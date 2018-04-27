#include "main.h"

PIDController::PIDController(Motor* outputMotor, float kP, float kI, float kD) {
  this->outputMotor = outputMotor;
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
  error = setpoint - currSensorValue;
  integral += error * (deltaTime / 1000);
  derivative  = (error - previousError) / (deltaTime / 1000);
  output = confineToRange(kP * error + kI * integral + kD * derivative);
  //printf("Error is %d and output is %d\n", error, output);
  outputMotor->setSpeed(output);
  previousError = error;
}

bool PIDController::atSetpoint() {
  bool atSetpoint = inRange(this->currSensorValue, setpoint - threshold, setpoint + threshold) && fabs(derivative) < 0.1;
  return atSetpoint;
}
