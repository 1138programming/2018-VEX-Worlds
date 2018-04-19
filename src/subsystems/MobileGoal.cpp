#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
  // Get mobile goal motor
  mobileGoalMotor = Motor::getMotor(mobileGoalPort);

  controller = new PIDController(mobileGoalMotor, 0.5, 0.0, 0.05);
  resetEncoder();
}

void MobileGoal::moveMobileGoal(int speed) {
  mobileGoalMotor->setSpeed(speed);
}

void MobileGoal::setSetpoint(int setpoint) {
  controller->setSetpoint(range(setpoint, -20, 1770));
}

void MobileGoal::lock() {
  controller->setSetpoint(getEncoder());
}

int MobileGoal::getSetpoint() {
  return controller->getSetpoint();
}

void MobileGoal::loop() {
  controller->sensorValue(getEncoder());
  controller->loop();
}

void MobileGoal::resetEncoder() {
  imeReset(mobileGoalI2CAddress);
  controller->setSetpoint(0); // Reset setpoint too
}

int MobileGoal::getEncoder() {
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
