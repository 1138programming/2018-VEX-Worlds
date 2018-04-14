//#include "main.h"
#include "armSubmodules/FourBar.h"
#include "armSubmodules/Wrist.h"
//#include "Wrist.h"

#ifndef ARM_H
#define ARM_H

class Arm {
  private:
    static Arm* instance;
    Wrist* wristSys;
    FourBar* fourBarSys;
    Arm();
  public:
    void moveWrist(int speed);
    void moveFourBar(int speed);
    void setFourBarSetpoint(int setpoint);
    int getFourBarSetpoint();
    void fourBarLoop();
    static Arm* getInstance();
};

#endif
