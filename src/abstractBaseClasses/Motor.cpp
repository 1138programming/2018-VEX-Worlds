#include "main.h"

Motor* Motor::motorInstances[MAX_MOTORS];

Motor::Motor(int channel) {
  this->channel = channel;
  this->multiplier = 1;
}

void Motor::setSpeed(int speed) {
  this->speed = range(speed) * this->multiplier;
  motorSet(this->channel, this->speed);
}

int Motor::getSpeed() {
  return this->speed;
}

void Motor::reverse() {
  this->multiplier = -1;
}

void Motor::init() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    motorInstances[i] = new Motor(i + 1);
  }
}

Motor* Motor::getMotor(int motorPort) {
  return motorInstances[motorPort - 1];
}
