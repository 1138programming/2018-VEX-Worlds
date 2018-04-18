#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor {
  private:
    int channel;
    int speed;
  public:
    void setSpeed(int speed);
    int getSpeed();
    Motor(int channel);
};

#endif
