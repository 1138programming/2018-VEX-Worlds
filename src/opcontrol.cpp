/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	//Define joystick input variables
	int leftSide, rightSide, wristChannel, fourBarChannel; // Joysticks channel values
	bool moGoalFwd, moGoalBck, stackCone, cllFwd, cllBck; // Button states
	bool stackingCone = false;

	//Create instances of subsystems
	Base* base = Base::getInstance();
	Arm* arm = Arm::getInstance();
	MobileGoal* moGoal = MobileGoal::getInstance();

	int pidSetpoint;
	while (true) {
		// Set joysticks
		leftSide = joystickGetAnalog(1, 3); // Left y-channel
		rightSide = joystickGetAnalog(1, 2); // Right y-channel
		wristChannel = joystickGetAnalog(2, 3); // Left y-channel
		fourBarChannel = joystickGetAnalog(2, 2); // Right y-channel

		// Set buttons
		moGoalFwd = joystickGetDigital(1, 6, JOY_DOWN);
		moGoalBck = joystickGetDigital(1, 6, JOY_UP);
		cllFwd = joystickGetDigital(2, 7, JOY_DOWN);
		cllBck = joystickGetDigital(2, 7, JOY_UP);
		stackCone = joystickGetDigital(2, 8, JOY_LEFT);

		// Move base
		base->moveBase(leftSide, rightSide);

		/*if(!stackingCone) {
			// Move wrist
			pidSetpoint = arm->getWristSetpoint() + ((encoderTicks / 100) * (wristChannel / KMaxJoystickValue));
			arm->setWristSetpoint(pidSetpoint);
			arm->wristLoop();

			// Move four bar
			pidSetpoint = arm->getFourBarSetpoint() + ((encoderTicks / 100) * (fourBarChannel / KMaxJoystickValue));
			arm->setFourBarSetpoint(pidSetpoint);
			arm->fourBarLoop();
		}*/

		//Basic control
		arm->moveWrist(wristChannel);
		arm->moveFourBar(fourBarChannel);

		// Move mobile goal
		if (moGoalFwd) {
			moGoal->moveMobileGoal(KMaxMotorSpeed);
		} else if(moGoalBck) {
			moGoal->moveMobileGoal(-KMaxMotorSpeed);
		} else {
			moGoal->moveMobileGoal(0);
		}

		// Start collector
		if (cllFwd) {
			arm->moveCollector(KMaxMotorSpeed); // Collector forward
		} else if(cllBck) {
			arm->moveCollector(-KMaxMotorSpeed); // Collector backward
		} else {
			arm->moveCollector(0); // Stop collector
		}

		// Start stacking a cone (stop if a cone is already being stacked)
		/*if (stackCone) {
			stackingCone = arm->startStackingCone();
		}*/

		delay(DELAY_TIME); // Small delay
	}
}
