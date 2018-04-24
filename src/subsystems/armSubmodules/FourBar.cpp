#include "main.h"

FourBar* FourBar::instance = 0;

FourBar::FourBar() {
  fourBarMotor = Motor::getMotor(fourBarPort);
  fourBarEncoder = encoderInit(fourBarEncoderTopPort, fourBarEncoderBottomPort, true);
  resetEncoder();
  //controller = new PIDController(fourBarMotor, 0.5, 0.0, 0.0);
}

void FourBar::move(int speed) {
  //speed = threshold(speed);
  //fourBarMotor->setSpeed(speed);
}

void FourBar::setSetpoint(int setpoint) {
  //controller->setSetpoint(setpoint);
}

void FourBar::lock() {
  //printf("%d\n", getEncoderValue());
  //controller->setSetpoint(getEncoderValue());
}

int FourBar::getSetpoint() {
  //return controller->getSetpoint();
  return 0;
}

void FourBar::loop() {
  //controller->sensorValue(getEncoderValue());
  //controller->loop();
}

bool FourBar::atSetpoint() {
  //return controller->atSetpoint();
  return true;
}

int FourBar::getEncoderValue() {
  //printf("Four bar encoder is %d\n", encoderGet(fourBarEncoder));
  //return encoderGet(fourBarEncoder);
  return 0;
}

void FourBar::resetEncoder() {
  //encoderReset(fourBarEncoder);
}

FourBar* FourBar::getInstance() {
  if(instance == 0) {
    instance = new FourBar();
  }

  return instance;
}
