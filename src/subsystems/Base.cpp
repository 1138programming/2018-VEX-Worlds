#include "main.h"

Base* Base::instance = 0;

Base::Base() {
  gyro = gyroInit(gyroPort, 196);
  ultrasonic = ultrasonicInit(ultrasonicEcho, ultrasonicPing);

  // Get left base motors
  leftFrontBaseMotor = Motor::getMotor(leftFrontBasePort);
  leftMiddleBaseMotor = Motor::getMotor(leftMiddleBasePort);
  leftRearBaseMotor = Motor::getMotor(leftRearBasePort);

  // Get right base motors
  rightFrontBaseMotor = Motor::getMotor(rightFrontBasePort);
  rightMiddleBaseMotor = Motor::getMotor(rightMiddleBasePort);
  rightRearBaseMotor = Motor::getMotor(rightRearBasePort);
}

/**
 * Move the base
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
void Base::moveBase(int left, int right) {
  left = threshold(left);
  right = threshold(right);

  //Left motors
  motorSet(leftFrontBase, left);
  motorSet(leftMiddleBase, left);
  motorSet(leftRearBase, left);

  //Right motors
  motorSet(rightFrontBase, right);
  motorSet(rightMiddleBase, right);
  motorSet(rightRearBase, right);
}

void Base::resetGyro() {
  gyroReset(gyro);
}

int Base::getGyro() {
  return gyroGet(gyro); // In degrees
}

void Base::resetEncoders() {
  imeReset(baseLeftI2CAddress);
  imeReset(baseRightI2CAddress);
}

int Base::getLeftIME() {
  int count;
  imeGet(baseLeftI2CAddress, &count);
  return count;
}

int Base::getRightIME() {
  int count;
  imeGet(baseRightI2CAddress, &count);
  return count;
}

int Base::getUltrasonic() {
  return ultrasonicGet(ultrasonic); // In centimeters
}

Base* Base::getInstance() {
    if (instance == 0) {
      instance = new Base();
    }

    return instance;
}
