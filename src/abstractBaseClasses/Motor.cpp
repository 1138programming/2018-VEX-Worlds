#include "main.h"

Motor* motorInstances[MAX_MOTORS];

Motor::Motor(int channel) {
  this->channel = channel;
}

void Motor::setSpeed(int speed) {
  this->speed = range(speed);
  motorSet(this->channel, this->speed);
}

int Motor::getSpeed() {
  return this->speed;
}

void Motor::init() {
  for (int i = 1; i <= 10; i++) {
    motorInstances[i] = new Motor(i);
  }
}

Motor* Motor::getMotor(int motorPort) {
  return motorInstances[motorPort];
}
