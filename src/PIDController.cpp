#include "main.h"

PIDController::PIDController(int motorChannel, float kP, float kI, float kD) {
  this->motorChannel = motorChannel;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  //this->controllers.push_back(this);
}

void PIDController::setKp(float kP) {
  this->kP = kP;
}

void PIDController::setKi(float kI) {
  this->kI = kI;
}

void PIDController::setKd(float kD) {
  this->kD = kD;
}

void PIDController::setSetpoint(int setpoint) {
  //printf("Setpoint set to %d\n", setpoint);
  this->setpoint = setpoint;
  integral = 0;
}

int PIDController::getSetpoint() {
  return this->setpoint;
}

void PIDController::sensorValue(int value) {
  this->currSensorValue = value;
}

void PIDController::setThreshold(int threshold) {
  this->threshold = threshold;
}

void PIDController::loop() {
  deltaTime = millis() - lastTime;
  lastTime = millis();
  int error, output;
  error = setpoint - currSensorValue;
  integral += error * (deltaTime / 1000);
  derivative  = (error - previousError) / (deltaTime / 1000);
  output = range(kP * error + kI * integral + kD * derivative);
  motorSet(motorChannel, output);
  previousError = error;
}

bool PIDController::atSetpoint() {
  if (range(currSensorValue, setpoint - threshold, setpoint + threshold) && fabs(derivative) < 0.1) {
      return true;
  }
  return false;
}
