#include "main.h"

Arm* Arm::instance = 0;

void Arm::moveWrist(int speed) {
  speed = threshold(speed);
  motorSet(wrist, speed);
}

void Arm::moveFourBar(int speed) {
  speed = threshold(speed);
  motorSet(fourBar, speed);
}

Arm* Arm::getInstance() {
  if (instance == 0) {
    instance = new Arm();
  }

  return instance;
}
