#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

class Motor {
  private:
    int channel;
    int speed;
    int multiplier;
    Motor(int channel);
    Motor* followers[MAX_FOLLOWERS];
    unsigned int numFollowers;
    Motor* master;
    bool following;
    void setMaster(Motor* motor);
    static Motor* motorInstances[MAX_MOTORS];
  public:
    void setSpeed(int speed);
    int getSpeed();
    void reverse();
    void addFollower(Motor* motor);
    static void init();
    int getChannel();
    static Motor* getMotor(int motorPort);
};

#endif
