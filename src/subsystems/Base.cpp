#include "main.h"

Base* Base::instance = 0;

Base::Base() {
  // Get left base motors
  leftFrontBaseMotor = Motor::getMotor(leftFrontBasePort);
  leftMiddleBaseMotor = Motor::getMotor(leftMiddleBasePort);
  leftRearBaseMotor = Motor::getMotor(leftRearBasePort);

  // Get right base motors
  rightFrontBaseMotor = Motor::getMotor(rightFrontBasePort);
  rightMiddleBaseMotor = Motor::getMotor(rightMiddleBasePort);
  rightRearBaseMotor = Motor::getMotor(rightRearBasePort);

  // Reverse motors
  leftRearBaseMotor->reverse();
  rightFrontBaseMotor->reverse();
  rightMiddleBaseMotor->reverse();
  //rightRearBaseMotor->reverse();

  // Set follower motors
  leftFrontBaseMotor->addFollower(leftMiddleBaseMotor);
  leftFrontBaseMotor->addFollower(leftRearBaseMotor);
  rightFrontBaseMotor->addFollower(rightMiddleBaseMotor);
  rightFrontBaseMotor->addFollower(rightRearBaseMotor);

  gyro = gyroInit(gyroPort, 196);
  ultrasonic = ultrasonicInit(ultrasonicEcho, ultrasonicPing);

  encoderReference = 0;
}

/**
 * Move the base
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
void Base::moveBase(int left, int right) {
  left = threshold((int)(left * this->multiplier));
  right = threshold((int)(right * this->multiplier));

  //Left motors
  leftFrontBaseMotor->setSpeed(left);
  //leftMiddleBaseMotor->setSpeed(left);
  //leftRearBaseMotor->setSpeed(left);

  //Right motors
  rightFrontBaseMotor->setSpeed(right);
  //rightMiddleBaseMotor->setSpeed(right);
  //rightRearBaseMotor->setSpeed(right);
}

bool Base::moveBaseTo(int target, int logValue, int threshold) {
  setReference();

  // Set speed. Speed should decrease as the base gets closer to the target value
  int averageEncoderValue = (int)((getRightIME() + getLeftIME()) / 2);
  int speed = (int)(floor((KMaxMotorSpeed * log(abs((encoderReference + target) - averageEncoderValue) + 1)) / log(logValue + 1)));
  speed *= (encoderReference + target) > averageEncoderValue ? 1 : -1;

  // Move base by speed
  moveBase(speed, speed);

  return inRange(target, target - threshold, target + threshold);
}

bool Base::turnBaseTo(int target, int logValue, int threshold, int direction) {
  int gyroValue = getGyro();
  gyroValue = (int)(gyroValue - (floor(gyroValue / 360) * 360));

  int rightAngle = target > gyroValue ? target - gyroValue : (360 - gyroValue) + target;
  int leftAngle = target > gyroValue ? (360 - gyroValue) + target : gyroValue - target;

  int speed = (int)(floor((KMaxMotorSpeed * log(abs(target - gyroValue) + 1)) / log(logValue + 1)));

  if (abs(direction) != 1) {
    if (rightAngle < leftAngle)
      moveBase(speed, -speed);
    else
      moveBase(-speed, speed);
  } else if (direction == 1) {
    moveBase(speed, -speed);
  } else if (direction == -1) {
    moveBase(-speed, speed);
  }

  return inRange(gyroValue, gyroValue - threshold, gyroValue + threshold);
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

void Base::setMultiplier(float multiplier) {
  this->multiplier = multiplier;
}

void Base::setReference() {
  encoderReference = (int)((getRightIME() + getLeftIME()) / 2);
}

Base* Base::getInstance() {
    if (instance == 0) {
      instance = new Base();
    }

    return instance;
}
