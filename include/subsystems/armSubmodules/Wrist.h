#ifndef WRIST_H
#define WRIST_H

#include "main.h"

class Wrist {
  private:
    static Wrist* instance;
    Encoder wristEncoder;
    PIDController* controller;
    Wrist();
  public:
    void move(int speed);
    void setSetpoint(int setpoint);
    int getSetpoint();
    void loop();
    bool atSetpoint();
    int getEncoderValue();
    void resetEncoder();
    static Wrist* getInstance();
};

#endif
