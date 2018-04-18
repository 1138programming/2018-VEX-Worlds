#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "subsystems/armSubmodules/FourBar.h"
#include "subsystems/armSubmodules/Wrist.h"
#include "subsystems/armSubmodules/Collector.h"

class Arm {
  private:
    static Arm* instance;
    Wrist* wrist;
    FourBar* fourBar;
    Collector* collector;
    TaskHandle task;
    static Semaphore semaphore;
    static void stackConeTask(void * parameter);
    void clearStep();
    Arm();
  public:
    void moveFourBar(int speed);
    void moveWrist(int speed);
    void moveCollector(int speed);
    void setFourBarSetpoint(int setpoint);
    void setWristSetpoint(int setpoint);
    void lockFourBar();
    void lockWrist();
    int getFourBarSetpoint();
    int getWristSetpoint();
    int getFourBarPosition();
    int getWristPosition();
    void fourBarLoop();
    void wristLoop();
    bool fourBarAtSetpoint();
    bool wristAtSetpoint();
    bool startStackingCone();
    static Arm* getInstance();
};

#endif
