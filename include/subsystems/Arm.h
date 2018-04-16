#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "subsystems/armSubmodules/FourBar.h"
#include "subsystems/armSubmodules/Wrist.h"

class Arm {
  private:
    static Arm* instance;
    Wrist* wristSys;
    FourBar* fourBarSys;
    TaskHandle task;
    static Semaphore semaphore;
    static void stackConeTask(void * parameter);
    Arm();
  public:
    void moveFourBar(int speed);
    void moveWrist(int speed);
    void setFourBarSetpoint(int setpoint);
    void setWristSetpoint(int setpoint);
    int getFourBarSetpoint();
    int getWristSetpoint();
    void fourBarLoop();
    void wristLoop();
    bool fourBarAtSetpoint();
    bool wristAtSetpoint();
    bool startStackingCone();
    static Arm* getInstance();
};

#endif
