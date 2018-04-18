#include "main.h"

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
