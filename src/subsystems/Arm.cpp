#include "main.h"

Arm* Arm::instance = 0;
Semaphore Arm::semaphore = 0;

Arm::Arm() {
   wristSys = Wrist::getInstance();
   fourBarSys = FourBar::getInstance();
   task = NULL;
}

void Arm::moveFourBar(int speed) {
  fourBarSys->move(speed);
}

void Arm::moveWrist(int speed) {
  wristSys->move(speed);
}

void Arm::setFourBarSetpoint(int setpoint) {
  fourBarSys->setSetpoint(setpoint);
}

void Arm::setWristSetpoint(int setpoint) {
  wristSys->setSetpoint(setpoint);
}

int Arm::getFourBarSetpoint() {
  return fourBarSys->getSetpoint();
}

int Arm::getWristSetpoint() {
  return wristSys->getSetpoint();
}

void Arm::fourBarLoop() {
  fourBarSys->loop();
}

void Arm::wristLoop() {
  wristSys->loop();
}
bool Arm::fourBarAtSetpoint() {
  return fourBarSys->atSetpoint();
}

bool Arm::wristAtSetpoint() {
  return wristSys->atSetpoint();
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

void Arm::stackConeTask(void * parameter) {
  unsigned int startTime;
  Arm* arm = instance;

  // Set four bar to top position
  startTime = millis();
  arm->setFourBarSetpoint((int)(fourBarEncoderTicks / 4));
  while(!arm->fourBarAtSetpoint() || millis() > startTime + 5000) { // PID loop
    arm->fourBarLoop();
    delay(delayTime);
  }

  // Set wrist to horizontal out from the robot
  startTime = millis();
  arm->setWristSetpoint((int)(encoderTicks * 0.75));
  while(!arm->wristAtSetpoint() || millis() > startTime + 5000) { // PID loop
    arm->wristLoop();
    arm->fourBarLoop();
    delay(delayTime);
  }

  //Gives up the semaphore
  semaphoreGive(semaphore);
}

Arm* Arm::getInstance() {
  if (instance == 0) {
    instance = new Arm();
  }

  return instance;
}
