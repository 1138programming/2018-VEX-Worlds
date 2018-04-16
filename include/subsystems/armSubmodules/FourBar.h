#include "main.h"

#ifndef FOURBAR_H
#define FOURBAR_H

class FourBar {
  private:
    static FourBar* instance;
    Encoder fourBarEncoder;
    PIDController* controller;
    FourBar();
  public:
    void move(int speed);
    void setSetpoint(int setpoint);
    int getSetpoint();
    void loop();
    bool atSetpoint();
    int getEncoderValue();
    static FourBar* getInstance();
};

#endif
