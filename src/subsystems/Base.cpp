#include "main.h"

Base* Base::instance = 0;

Base::Base() {
  encoderTicks = 20;
}

/**
 * Move the base
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
void Base::moveBase(int left, int right) {
  left = threshold(left);
  right = -threshold(right);

  //Left motors
  motorSet(leftFrontBase, left);
  motorSet(leftMiddleBase, left);
  motorSet(leftRearBase, left);

  //Right motors
  motorSet(rightFrontBase, right);
  motorSet(rightMiddleBase, right);
  motorSet(rightRearBase, right);
}

Base* Base::getInstance() {
    if (instance == 0) {
      instance = new Base();
    }

    return instance;
}
