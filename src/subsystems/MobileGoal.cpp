#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
}

void MobileGoal::moveMobileGoal(int speed) {
  speed = threshold(speed);
  motorSet(leftMobileGoal, speed);
  motorSet(rightMobileGoal, speed);
}

MobileGoal* MobileGoal::getInstance() {
  if (instance == 0) {
    instance = new MobileGoal();
  }

  return instance;
}
