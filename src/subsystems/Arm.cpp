#include "main.h"

Arm* Arm::instance = 0;
Semaphore Arm::semaphore = 0;

Arm::Arm() {
   wrist = Wrist::getInstance();
   fourBar = FourBar::getInstance();
   collector = Collector::getInstance();
   task = NULL;
}

void Arm::moveFourBar(int speed) {
  fourBar->move(speed);
}

void Arm::moveWrist(int speed) {
  wrist->move(speed);
}

void Arm::moveCollector(int speed) {
  collector->move(speed);
}

void Arm::setFourBarSetpoint(int setpoint) {
  fourBar->setSetpoint(setpoint);
}

void Arm::setWristSetpoint(int setpoint) {
  wrist->setSetpoint(setpoint);
}

void Arm::lockFourBar() {
  fourBar->lock();
}

void Arm::lockWrist() {
  wrist->lock();
}

int Arm::getFourBarSetpoint() {
  return fourBar->getSetpoint();
}

int Arm::getFourBarPosition() {
  return fourBar->getEncoderValue();
}

int Arm::getWristSetpoint() {
  return wrist->getSetpoint();
}

int Arm::getWristPosition() {
  return wrist->getEncoderValue();
}

void Arm::fourBarLoop() {
  fourBar->loop();
}

void Arm::wristLoop() {
  wrist->loop();
}
bool Arm::fourBarAtSetpoint() {
  return fourBar->atSetpoint();
}

bool Arm::wristAtSetpoint() {
  return wrist->atSetpoint();
}

bool Arm::startStackingCone() {
  if (semaphoreTake(semaphore, 0)) {
    task = taskCreate(stackConeTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    return true;
  }
  if (task != NULL) {
    taskDelete(task);
    semaphoreGive(semaphore);
    task = NULL;
  }
  return false;
}

// Stack cone task
void Arm::stackConeTask(void * parameter) {
  Arm* arm = instance; // Gets the arm subsystem
  unsigned int startTime; // This variable will save the time at which main loop of the task starts
  unsigned int timeStamp; // This variable will save the time at which each step in the loop starts
  int step = 0; // The step the task is on
  int totalSteps = 7; // Total number of steps

  // Update timeStamp and increment step
  auto clearStep = [&] {
    timeStamp = millis();
    step++;
  };

  // Set four bar to top position and set wrist to point downwards
  startTime = millis();
  timeStamp = millis();

  //Loop which will run until the steps are finished or after 20 seconds have passed as a precaution
  while(step < totalSteps && millis() < startTime + DEFAULT_TASK_TIME) {
    switch(step) {
      case 0: // Lift the four bar and make the wrist point downward
        arm->setFourBarSetpoint((int)(fourBarEncoderTicks * 0.25));
        arm->setWristSetpoint((int)(encoderTicks * 0.75));
        clearStep();
        return;
      case 1: // Loop the four bar and wrist until they are at the setpoint
        arm->fourBarLoop();
        arm->wristLoop();
        if(arm->fourBarAtSetpoint() && arm->wristAtSetpoint())
          clearStep();
        return;
      case 2: // Lower the four bar and start running the collector
        arm->setFourBarSetpoint(0);
        arm->moveCollector(127);
        clearStep();
        return;
      case 3: // Loop the four bar and wrist until the four bar is at the setpoint
        arm->fourBarLoop();
        arm->wristLoop();
        if(arm->fourBarAtSetpoint())
          clearStep();
        return;
      case 4: // Wait half a second for the collector to pick up the cone
        arm->fourBarLoop();
        arm->wristLoop();
        if(millis() - timeStamp > 500)
          clearStep();
        return;
      case 5: // Lift the four bar and stop the collector
        arm->setFourBarSetpoint((int)(fourBarEncoderTicks * 0.25));
        arm->moveCollector(0);
        clearStep();
        return;
      case 6: // Loop the four bar and wrist until the four bar is at the setpoint
        arm->fourBarLoop();
        arm->wristLoop();
        if(arm->fourBarAtSetpoint())
          clearStep();
        return;
    }

    delay(DELAY_TIME);
  }

  // Gives up the semaphore, allowing this task to be called again later
  semaphoreGive(semaphore);
}

Arm* Arm::getInstance() {
  if (instance == 0) {
    instance = new Arm();
  }

  return instance;
}
