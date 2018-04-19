#include "main.h"

Wrist* Wrist::instance = 0;

Wrist::Wrist() {
  wristMotor = Motor::getMotor(wristPort);
  //wristEncoder = encoderInit(wristEncoderTopPort, wristEncoderBottomPort, false);
  resetEncoder();
  controller = new PIDController(wristMotor, 1.0, 0, 0);
}

void Wrist::move(int speed) {
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
  int count;
  imeGet(wristI2CAddress, &count);
  return count;
}

void Wrist::resetEncoder() {
  imeReset(wristI2CAddress);
  controller->setSetpoint(0); // Reset setpoint too
}

Wrist* Wrist::getInstance() {
  if(instance == 0) {
    instance = new Wrist();
  }

  return instance;
}
