#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor {
  private:
    int channel;
    int speed;
    int multiplier = 1;
    Motor(int channel);
    static Motor* motorInstances[MAX_MOTORS];
  public:
    void setSpeed(int speed);
    int getSpeed();
    void reverse();
    static void init();
    static Motor* getMotor(int motorPort);
};

#endif
