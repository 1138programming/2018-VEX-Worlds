#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor {
  private:
    int channel;
    int speed;
    Motor(int channel);
    static Motor* motorInstances[];
  public:
    void setSpeed(int speed);
    int getSpeed();
    static void init();
    static Motor* getMotor(int motorPort);
};

#endif
