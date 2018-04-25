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
  rightRearBaseMotor->reverse();

  gyro = gyroInit(gyroPort, 196);
  ultrasonic = ultrasonicInit(ultrasonicEcho, ultrasonicPing);
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
  leftMiddleBaseMotor->setSpeed(left);
  leftRearBaseMotor->setSpeed(left);
  //motorSet(leftFrontBase, left);
  //motorSet(leftMiddleBase, left);
  //motorSet(leftRearBase, left);

  //Right motors
  rightFrontBaseMotor->setSpeed(right);
  rightMiddleBaseMotor->setSpeed(right);
  rightRearBaseMotor->setSpeed(right);
  //motorSet(rightFrontBase, right);
  //motorSet(rightMiddleBase, right);
  //motorSet(rightRearBase, right);
}

void Base::setSetpoint(int leftSetpoint, int rightSetpoint) {
  resetEncoders();
  this->leftBaseSetpoint = leftSetpoint;
  this->rightBaseSetpoint = rightSetpoint;
}

void Base::loop() {
  float leftkP = 0.5;
  float rightkP = 0.5;
  moveBase(
    (int)(leftkP * (leftBaseSetpoint - getLeftIME())),
    (int)(rightkP * (rightBaseSetpoint - getRightIME()))
  );
  printf("Left IME is %d\n", getLeftIME());
  printf("Right IME is %d\n", getRightIME());
}

bool Base::atSetpoint() {
  return (leftBaseSetpoint - getLeftIME() <= 10) && (rightBaseSetpoint - getRightIME() <= 10);
}

bool Base::turnDegrees(int degrees, float logValue, int direction) {
  // int gyro = getGyro();
  // float rightAngle = degrees > gyro ? degrees - gyro : (360 - gyro) + degrees;
  // float leftAngle = degrees > gyro ? (360 - gyro) + gyro : gyro - degrees;
  //
  // float speed = floor((KMaxMotorSpeed * log(abs(gyro - degrees) + 1)) / (log(logValue + 1)));
  //
  // if (abs(direction) != 1) {
  //   if (rightAngle < leftAngle) {
  //     moveBase(speed, -speed);
  //   } else {
  //     moveBase(-speed, speed);
  //   }
  // } else if (direction == 1) {
  //   moveBase(speed, -speed);
  // } else if (direction == -1) {
  //   moveBase(-speed, speed);
  // }
  // return threshold(speed, 15) < 15;
  return false;
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

Base* Base::getInstance() {
    if (instance == 0) {
      instance = new Base();
    }

    return instance;
}
