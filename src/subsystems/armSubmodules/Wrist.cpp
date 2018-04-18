#include "main.h"

Wrist* Wrist::instance = 0;

Wrist::Wrist() {
  wristEncoder = encoderInit(wristEncoderTopPort, wristEncoderBottomPort, false);
  resetEncoder();
  controller = new PIDController(wristPort, 1.0, 0, 0);
}

void Wrist::move(int speed) {
  speed = threshold(speed);
  motorSet(wristPort, speed);
}

void Wrist::setSetpoint(int setpoint) {
  controller->setSetpoint(setpoint);
}

void Wrist::lock() {
  controller->setSetpoint(getEncoderValue());
}

int Wrist::getSetpoint() {
  return controller->getSetpoint();
}

void Wrist::loop() {
  controller->sensorValue(getEncoderValue());
  controller->loop();
}

bool Wrist::atSetpoint() {
  return controller->atSetpoint();
}

int Wrist::getEncoderValue() {
  return encoderGet(wristEncoder);
}

void Wrist::resetEncoder() {
  encoderReset(wristEncoder);
}

Wrist* Wrist::getInstance() {
  if(instance == 0) {
    instance = new Wrist();
  }

  return instance;
}
