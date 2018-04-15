#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "armSubmodules/FourBar.h"
#include "armSubmodules/Wrist.h"

class Arm {
  private:
    static Arm* instance;
    Wrist* wristSys;
    FourBar* fourBarSys;
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
    static Arm* getInstance();
};

#endif
