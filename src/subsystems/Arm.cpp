#include "main.h"

Arm* Arm::instance = 0;

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

int Arm::getWristSetpoint() {
  return wrist->getSetpoint();
}

int Arm::getFourBarPosition() {
  return fourBar->getEncoderValue();
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

void Arm::startStackingCone() {
  if (checkStackConeTask()) {
    printf("Deleting task\n");
    taskDelete(task);
  } else {
    printf("Creating new task\n");
    task = taskCreate(stackConeTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  }
  delay(DELAY_TIME); // Allow a.) The idle task to free memory, or 2.) The new task to run
}

bool Arm::checkStackConeTask() {
  return task && taskGetState(task) == TASK_RUNNING || taskGetState(task) == TASK_SLEEPING;
}

// Stack cone task
void Arm::stackConeTask(void * parameter) {
  printf("Stack cone task created");

  Arm* arm = getInstance(); // Gets the arm subsystem
  unsigned int startTime; // This variable will save the time at which main loop of the task starts to make sure the while loop doesn't run for too long
  unsigned int timeStamp; // This variable keeps track of the time at the beginning of each step to allow for time based steps
  int step = 0; // The step the task is on
  int totalSteps = 7; // Total number of steps

  // Initialize startTime and timeStamp
  startTime = millis();

  // Move arm and wrist upwards to grab a cone
  arm->setFourBarSetpoint((int)(fourBarEncoderTicks * 0.25));
  arm->setWristSetpoint((int)(wristRotationTicks * -0.40));
  while (!arm->fourBarAtSetpoint() && !arm->wristAtSetpoint() && millis() < (startTime + DEFAULT_TASK_TIME)) {
    arm->fourBarLoop();
    arm->wristLoop();
  }
  arm->setFourBarSetpoint(0); // Move the arm down to
  while (!arm->fourBarAtSetpoint() && millis() < (startTime + DEFAULT_TASK_TIME)) {
    arm->fourBarLoop();
    arm->wristLoop();
  }
  arm->setFourBarSetpoint((int)(fourBarEncoderTicks * 0.25));
  arm->setWristSetpoint((int)(wristRotationTicks * 0.25));
  while (!arm->fourBarAtSetpoint() && !arm->wristAtSetpoint() && millis() < (startTime + DEFAULT_TASK_TIME)) {
    arm->fourBarLoop();
    arm->wristLoop();
  }
  arm->setFourBarSetpoint(0);
  arm->setWristSetpoint((int)(wristRotationTicks));
  while (!arm->fourBarAtSetpoint() && !arm->wristAtSetpoint() && millis() < (startTime + DEFAULT_TASK_TIME)) {
    arm->fourBarLoop();
    arm->wristLoop();
  }
  // The loop has ended. All the steps have run, or the robot took to long and the DEFAULT_TASK_TIME elapsed

  // Stop all motors
  arm->lockWrist();
  arm->lockFourBar();
}

Arm* Arm::getInstance() {
  if (instance == 0) {
    instance = new Arm();
  }

  return instance;
}
