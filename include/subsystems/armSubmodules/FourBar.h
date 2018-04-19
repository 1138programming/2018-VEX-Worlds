#include "main.h"

#ifndef FOURBAR_H
#define FOURBAR_H

class FourBar {
  private:
    static FourBar* instance;
    Encoder fourBarEncoder;
    PIDController* controller;
    Motor* fourBarMotor;
    FourBar();
  public:
    void move(int speed);
    void setSetpoint(int setpoint);
    void lock();
    int getSetpoint();
    void loop();
    bool atSetpoint();
    int getEncoderValue();
    void resetEncoder();
    static FourBar* getInstance();
};

#endif
