#include "main.h"

Arm* Arm::instance = 0;

Arm::Arm() {
   wristSys = Wrist::getInstance();
   fourBarSys = FourBar::getInstance();
}

void Arm::moveFourBar(int speed) {
  fourBarSys->move(speed);
}

void Arm::moveWrist(int speed) {
  wristSys->move(speed);
}

void Arm::setFourBarSetpoint(int setpoint) {
  fourBarSys->setSetpoint(setpoint);
}

void Arm::setWristSetpoint(int setpoint) {
  wristSys->setSetpoint(setpoint);
}

int Arm::getFourBarSetpoint() {
  return fourBarSys->getSetpoint();
}

int Arm::getWristSetpoint() {
  return wristSys->getSetpoint();
}

void Arm::fourBarLoop() {
  fourBarSys->loop();
}

void Arm::wristLoop() {
  wristSys->loop();
}

Arm* Arm::getInstance() {
  if (instance == 0) {
    instance = new Arm();
  }

  return instance;
}
