#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
  // Get mobile goal motor
  mobileGoalMotor = Motor::getMotor(mobileGoalPort);

  controller = new PIDController(mobileGoalMotor, 0.5, 0.0, 0.05);
  //rightController = new PIDController(leftMobileGoalMotor, 0.5, 0.0, 0.05);
  resetIME();
}

void MobileGoal::moveMobileGoal(int speed) {
  mobileGoalMotor->setSpeed(speed);
  //rightMobileGoalMotor->setSpeed(speed);
}

void MobileGoal::setSetpoint(int setpoint) {
  //controller->setSetpoint(range(setpoint, -20, 1770));
  controller->setSetpoint(setpoint);
  //rightController->setSetpoint(setpoint);
}

void MobileGoal::lock() {
  controller->setSetpoint(getIME());
  //rightController->setSetpoint(getIME());
}

int MobileGoal::getSetpoint() {
  return controller->getSetpoint();
}

void MobileGoal::loop() {
  controller->sensorValue(getIME());
  controller->loop();
  //rightController->sensorValue(getIME());
  //rightController->loop();
}

void MobileGoal::resetIME() {
  imeReset(mobileGoalI2CAddress);
  controller->setSetpoint(0); // Reset setpoint too
  //rightController->setSetpoint(0); // Reset setpoint too
}

int MobileGoal::getIME() {
  int count;
  imeGet(mobileGoalI2CAddress, &count);
  return count;
}

bool MobileGoal::atSetpoint() {
  return controller->atSetpoint();
}

MobileGoal* MobileGoal::getInstance() {
  if (instance == 0) {
    instance = new MobileGoal();
  }

  return instance;
}
