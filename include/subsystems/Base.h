#ifndef BASE_H
#define BASE_H

#include "main.h"

class Base {
  private:
    static Base* instance;
    Gyro gyro;
    Ultrasonic ultrasonic;

    // Left base motors
    Motor* leftFrontBaseMotor;
    Motor* leftMiddleBaseMotor;
    Motor* leftRearBaseMotor;

    // Right base motors
    Motor* rightFrontBaseMotor;
    Motor* rightMiddleBaseMotor;
    Motor* rightRearBaseMotor;
    
    Base();
  public:
    void moveBase(int left, int right);
    void resetGyro();
    int getGyro();
    void resetEncoders();
    int getLeftIME();
    int getRightIME();
    int getUltrasonic();
    static Base* getInstance();
};

#endif
