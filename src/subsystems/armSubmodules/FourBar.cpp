#include "main.h"

FourBar* FourBar::instance = 0;

FourBar::FourBar() {
  fourBarEncoder = encoderInit(fourBarEncoderTopPort, fourBarEncoderBottomPort, false);
  controller = new PIDController(fourBar, 0.1, 0, 0);
}

void FourBar::move(int speed) {
  speed = threshold(speed);
  motorSet(fourBar, speed);
}

void FourBar::setSetpoint(int setpoint) {
  controller->setSetpoint(setpoint);
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
  return encoderGet(fourBarEncoder);
}

FourBar* FourBar::getInstance() {
  if(instance == 0) {
    instance = new FourBar();
  }

  return instance;
}
