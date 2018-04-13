/** @file Constants.h
 * @brief Provides constants used throughout the entire code. Contains user-readable motor names
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "main.h"
//#include "subsystems/Claw.h"
//#include "subsystems/Arm.h"
#include "subsystems/Base.h"

// Motors
const int rightFrontBase = 1;
const int wrist = 2;
const int rightMobileGoal = 3;
const int rightMiddleBase = 4;
const int leftMobileGoal = 5;
const int leftFrontBase = 6;
const int arm = 7;
const int leftMiddleBase = 8;
const int leftRearBase = 9;
const int rightRearBase = 10;

// Analog Sensors
const int autonPotentiometer = 1;
const int gyroSensor = 2;

// Digital Sensors
//const int clawPneumatic = 1;
const int fourBarLimitSwitch = 6;

// Other Sensors
const float rotationsPerInch = 31.400156410256;

#endif
