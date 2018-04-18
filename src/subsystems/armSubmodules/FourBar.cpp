#include "main.h"

FourBar* FourBar::instance = 0;

FourBar::FourBar() {
  fourBarEncoder = encoderInit(fourBarEncoderTopPort, fourBarEncoderBottomPort, true);
  resetEncoder();
  controller = new PIDController(fourBarPort, 0.5, 0.0, 0.0);
}

void FourBar::move(int speed) {
  speed = threshold(speed);
  motorSet(fourBarPort, speed);
}

void FourBar::setSetpoint(int setpoint) {
  controller->setSetpoint(setpoint);
}

void FourBar::lock() {
  printf("%d\n", getEncoderValue());
  controller->setSetpoint(getEncoderValue());
}

int FourBar::getSetpoint() {
  return controller->getSetpoint();
}

void FourBar::loop() {
  int encoderValue = getEncoderValue();
  controller->sensorValue(encoderValue);
  controller->loop();
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
