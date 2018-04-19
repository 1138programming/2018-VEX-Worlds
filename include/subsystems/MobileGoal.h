#ifndef MOBILEGOAL_H
#define MOBILEGOAL_H

#include "abstractBaseClasses/PIDController.h"

class MobileGoal {
  private:
    int encoderTicks;
    PIDController* controller;
    static MobileGoal* instance;
    Motor* mobileGoalMotor;
    MobileGoal();
  public:
    void moveMobileGoal(int speed);
    void loop();
    void setSetpoint(int setpoint);
    void lock();
    int getSetpoint();
    void resetEncoder();
    int getEncoder();
    static MobileGoal* getInstance();
};

#endif
