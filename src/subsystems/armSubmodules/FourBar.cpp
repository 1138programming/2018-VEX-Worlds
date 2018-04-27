#include "main.h"

FourBar* FourBar::instance = 0;

FourBar::FourBar() {
  fourBarMotor = Motor::getMotor(fourBarPort);

  fourBarEncoder = encoderInit(fourBarEncoderTopPort, fourBarEncoderBottomPort, true);
  resetEncoder();

  controller = new PIDController(fourBarMotor, 0.9, 0.01, 0.0);
  controller->setThreshold(20);
  //topController = new PIDController(bottomFourBarMotor, 0.7, 0.0, 0.0);
}

void FourBar::move(int speed) {
  //topFourBarMotor->setSpeed(speed);
  fourBarMotor->setSpeed(speed);
}

void FourBar::setSetpoint(int setpoint) {
  controller->setSetpoint(setpoint);
  //topController->setSetpoint(setpoint);
}

void FourBar::lock() {
  //printf("%d\n", getEncoderValue());
  controller->setSetpoint(getEncoderValue());
  //topController->setSetpoint(getEncoderValue());
}

int FourBar::getSetpoint() {
  return controller->getSetpoint();
}

void FourBar::loop() {
  controller->sensorValue(getEncoderValue());
  controller->loop();
  //topController->sensorValue(getEncoderValue());
  //topController->loop();
}

bool FourBar::atSetpoint() {
  return controller->atSetpoint();
}

int FourBar::getEncoderValue() {
  //printf("Four bar encoder is %d\n", encoderGet(fourBarEncoder));
  return encoderGet(fourBarEncoder);
}

void FourBar::resetEncoder() {
  encoderReset(fourBarEncoder);
}

FourBar* FourBar::getInstance() {
  if(instance == 0) {
    instance = new FourBar();
  }

  return instance;
}
