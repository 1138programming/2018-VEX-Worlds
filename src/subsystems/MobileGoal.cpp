#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
  mogoController = new PIDController(mobileGoalPort, 0.5, 0.0, 0.05);
  resetIME();
}

void MobileGoal::moveMobileGoal(int speed) {
  speed = threshold(speed);
  motorSet(mobileGoalPort, speed);
  //motorSet(rightMobileGoal, speed);
}

void MobileGoal::setSetpoint(int setpoint) {
  mogoController->setSetpoint(range(setpoint, -20, 1770));
}

void MobileGoal::loop() {
  mogoController->sensorValue(getIME());
  mogoController->loop();
}

void MobileGoal::resetIME() {
  imeReset(mobileGoalI2CAddress);
  mogoController->setSetpoint(0); // Reset setpoint too
}

int MobileGoal::getIME() {
  int count;
  imeGet(mobileGoalI2CAddress, &count);
  return count;
}

MobileGoal* MobileGoal::getInstance() {
  if (instance == 0) {
    instance = new MobileGoal();
  }

  return instance;
}
