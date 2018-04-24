#include "main.h"

Wrist* Wrist::instance = 0;

Wrist::Wrist() {
  wristMotor = Motor::getMotor(wristPort);
  //wristEncoder = encoderInit(wristEncoderTopPort, wristEncoderBottomPort, false);
  //resetEncoder();
  imeReset(wristIME);
  controller = new PIDController(wristMotor, 1.0, 0, 0);
}

void Wrist::move(int speed) {
  speed = threshold(speed);
  wristMotor->setSpeed(speed);
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
  //return encoderGet(wristEncoder);
  int count;
  imeGet(wristIME, &count);
  return count;
}

void Wrist::resetEncoder() {
  //encoderReset(wristEncoder);
  imeReset(wristIME);
}

Wrist* Wrist::getInstance() {
  if(instance == 0) {
    instance = new Wrist();
  }

  return instance;
}
