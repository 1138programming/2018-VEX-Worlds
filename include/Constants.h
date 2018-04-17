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

#define DEFAULT_TASK_TIME 20000
#define DELAY_TIME 10

// Motors
// Left base motors
const int leftFrontBase = 6;
const int leftMiddleBase = 8;
const int leftRearBase = 9;

// Right base motors
const int rightFrontBase = 1;
const int rightMiddleBase = 4;
const int rightRearBase = 10;

// Mobile goal motor
const int mobileGoalPort = 5;
//const int rightMobileGoal = 3;

//Collector motor
const int collectorPort = 3;

// Arm submodule motors
const int wristPort = 2;
const int fourBarPort = 7;


// IME Addresses
const unsigned char mobileGoalI2CAddress = 0;
const unsigned char baseLeftI2CAddress = 1;
const unsigned char baseRightI2CAddress = 2;


//Motor and encoder constants
const int KMaxMotorSpeed = 127;
const int KMaxJoystickValue = 127;
const int encoderTicks = 90; // Encoder ticks in one revolution
const int fourBarEncoderTicks = 450; // Accounts for the 5:1 gear ratio


// Analog Sensors
//const int autonPotentiometer = 1;
const int gyroPort = 1;


// Digital Sensors
//const int clawPneumatic = 1;
const int fourBarLimitSwitch = 1;
const int ultrasonicPing = 4;
const int ultrasonicEcho = 5;
const int fourBarEncoderTopPort = 6;
const int fourBarEncoderBottomPort = 7;
const int wristEncoderTopPort = 8;
const int wristEncoderBottomPort = 9;


// Other constants
const float rotationsPerInch = 31.400156410256; // TODO check if this is correct

#endif
