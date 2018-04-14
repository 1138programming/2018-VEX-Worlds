/**
 * @file Constants.h
 * @brief Provides constants used throughout the entire code. Contains user-readable motor names
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


#include "main.h"
//#include "subsystems/Base.h"
//#include "subsystems/Arm.h"
//#include "subsystems/MobileGoal.h"


// Motors
// Left base motors
const int leftFrontBase = 6;
const int leftMiddleBase = 8;
const int leftRearBase = 9;

// Right base motors
const int rightFrontBase = 1;
const int rightMiddleBase = 4;
const int rightRearBase = 10;

// Mobile goal motors
const int leftMobileGoal = 5;
const int rightMobileGoal = 3;

// Wrist and arm motors
const int wrist = 2;
const int fourBar = 7;


//Motor and encoder constants
const int KMaxMotorSpeed = 127;
const int encoderTicks = 90; // Encoder ticks in one revolution
const int fourBarEncoderTicks = 450; // Accounts for the 5:1 gear ratio


// Analog Sensors
//const int autonPotentiometer = 1;
//const int gyroSensor = 2;


// Digital Sensors
//const int clawPneumatic = 1;
const int fourBarLimitSwitch = 5;
const int fourBarEncoderTopPort = 6;
const int fourBarEncoderBottomPort = 7;

// Other Sensors
const float rotationsPerInch = 31.400156410256; // TODO check if this is correct

#endif
