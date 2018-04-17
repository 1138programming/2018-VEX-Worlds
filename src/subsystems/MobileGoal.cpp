#include "main.h"

MobileGoal* MobileGoal::instance = 0;

MobileGoal::MobileGoal() {
}

void MobileGoal::moveMobileGoal(int speed) {
  speed = threshold(speed);
  motorSet(mobileGoalPort, speed);
  //motorSet(rightMobileGoal, speed);
}

void resetIME() {
  imeReset(mobileGoalI2CAddress);
}

int MobileGoal::getIME() {
  int count;
  imeGet(mobileGoalI2CAddress, &count);
  return count;
}

MobileGoal* MobileGoal::getInstance() {
  if (instance == 0) {
    instance = new MobileGoal();
  }

  return instance;
}
