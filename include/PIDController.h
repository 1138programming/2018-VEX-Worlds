#ifndef _SUBSYSTEMS_PIDCONTROLLER_H_
#define _SUBSYSTEMS_PIDCONTROLLER_H_

class PIDController {
  private:
    float kP = 0;
    float kI = 0;
    float kD = 0;
    int motorChannel = 0;
    long integral = 0;
    int previousError = 0;
    int setpoint = 0;
    int currSensorValue = 0;
    float deltaTime = 0;
    int lastTime = 0;
  public:
    PIDController(int motorChannel, float kP = 1, float kI = 0, float kD = 0);
    void setKp(float kP);
    void setKi(float kI);
    void setKd(float kD);
    void setSetpoint(int setpoint);
    int getSetpoint();
    void sensorValue(int value);
    void loop();
};

#endif
