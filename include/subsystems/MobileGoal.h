#ifndef MOBILEGOAL_H
#define MOBILEGOAL_H

#include "abstractBaseClasses/PIDController.h"

class MobileGoal {
  private:
    int encoderTicks;
    PIDController* controller;
    // PIDController* rightController;
    static MobileGoal* instance;
    Motor* mobileGoalMotor;
    MobileGoal();
  public:
    void moveMobileGoal(int speed);
    void loop();
    void setSetpoint(int setpoint);
    bool atSetpoint();
    void lock();
    int getSetpoint();
    void resetIME();
    int getIME();
    static MobileGoal* getInstance();
};

#endif
