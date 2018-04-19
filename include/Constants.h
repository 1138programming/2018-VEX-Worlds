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

#define DEFAULT_TASK_TIME 3500
#define DELAY_TIME 10
#define MAX_MOTORS 10

// Motor ports
// Left base motor ports
const int leftFrontBasePort = 6;
const int leftMiddleBasePort = 8;
const int leftRearBasePort = 9;

// Right base motor ports
const int rightFrontBasePort = 1;
const int rightMiddleBasePort = 4;
const int rightRearBasePort = 10;

// Mobile goal moto port
const int mobileGoalPort = 5;
//const int rightMobileGoal = 3;

//Collector motor port
const int collectorPort = 3;

// Arm submodule motor ports
const int wristPort = 2;
const int fourBarPort = 7;


// IME Addresses
const unsigned char mobileGoalI2CAddress = 0;
const unsigned char baseLeftI2CAddress = 1;
const unsigned char baseRightI2CAddress = 2;
const unsigned char wristI2CAddress = 3;


//Motor and encoder constants
const int KMaxMotorSpeed = 127;
const int KMaxJoystickValue = 127;
const int encoderTicks = 360; // Encoder ticks in one revolution
const int fourBarEncoderTicks = 5 * encoderTicks; // Accounts for the 5:1 gear ratio


// Analog Sensors
//const int autonPotentiometer = 1;
const int gyroPort = 1;


// Digital Sensors
//const int clawPneumatic = 1;
const int fourBarLimitSwitch = 1;
const int ultrasonicPing = 4;
const int ultrasonicEcho = 5;
const int fourBarEncoderTopPort = 7;
const int fourBarEncoderBottomPort = 6;
const int wristEncoderTopPort = 9;
const int wristEncoderBottomPort = 8;


// Other constants
const float rotationsPerInch = 31.400156410256; // TODO check if this is correct

#endif
