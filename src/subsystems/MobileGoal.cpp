#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
  // Get mobile goal motor
  mobileGoalMotor = Motor::getMotor(mobileGoalPort);

  controller = new PIDController(mobileGoalMotor, 0.5, 0.0, 0.05);
  resetIME();
}

void MobileGoal::moveMobileGoal(int speed) {
  speed = threshold(speed);
  mobileGoalMotor->setSpeed(speed);
}

void MobileGoal::setSetpoint(int setpoint) {
  controller->setSetpoint(range(setpoint, -20, 1770));
}

void MobileGoal::lock() {
  controller->setSetpoint(getIME());
}

int MobileGoal::getSetpoint() {
  return controller->getSetpoint();
}

void MobileGoal::loop() {
  controller->sensorValue(getIME());
  controller->loop();
}

void MobileGoal::resetIME() {
  imeReset(mobileGoalI2CAddress);
  controller->setSetpoint(0); // Reset setpoint too
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
