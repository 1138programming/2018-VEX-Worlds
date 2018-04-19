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
	bool moGoalFwd, moGoalBck, stackCone, cllFwd, cllBck, slowMode; // Button states
	bool stackingCone = false;

	//Create instances of subsystems
	Base* base = Base::getInstance();
	Arm* arm = Arm::getInstance();
	MobileGoal* moGoal = MobileGoal::getInstance();

	int deltaArm, deltaWrist;

	/*int startTime;
	startTime = millis();
	int toSet;
	toSet = (int)(fourBarEncoderTicks * 0.25);
	printf("toSet: %d\n", toSet);
	arm->setFourBarSetpoint(toSet);
	while((millis() - startTime) < 2500) {
		//arm->fourBarLoop();
		//printf("Milliseconds: %d\n", (int)(millis() - startTime));
		delay(DELAY_TIME);
	}

	printf("Four bar setpoint set to %d\n", arm->getFourBarSetpoint());

	while(true) {
		arm->fourBarLoop();

		//if (arm->fourBarAtSetpoint())
		//	printf("Four bar at setpoint \n");
		delay(DELAY_TIME);
	}*/
	while (true) {
		// Set joysticks
		leftSide = joystickGetAnalog(1, 3); // Left y-channel
		rightSide = joystickGetAnalog(1, 2); // Right y-channel
		wristChannel = joystickGetAnalog(2, 3); // Left y-channel
		fourBarChannel = joystickGetAnalog(2, 2); // Right y-channel

		// Set buttons
		moGoalFwd = joystickGetDigital(1, 6, JOY_DOWN);
		moGoalBck = joystickGetDigital(1, 6, JOY_UP);
		cllFwd = joystickGetDigital(2, 5, JOY_UP);
		cllBck = joystickGetDigital(2, 5, JOY_DOWN);
		stackCone = joystickGetDigital(2, 8, JOY_LEFT);
		slowMode = joystickGetDigital(1, 5, JOY_UP);

		// Set to slow mode
		if (slowMode) {
			base->setMultiplier(0.333);
		} else {
			base->setMultiplier(1);
		}

		// Move base
		base->moveBase(leftSide, rightSide);

		if (!stackingCone) {
			// Move the wrist
			deltaWrist = threshold(wristChannel, 10);
			if (deltaWrist) {
				arm->moveWrist(deltaWrist);
				arm->lockWrist();
				//arm->setWristSetpoint(arm->getWristPosition());
			} else {
				arm->wristLoop();
			}
			printf("Wrist encoder value: %d\n", arm->getWristPosition());

			// Move four bar
			deltaArm = threshold(fourBarChannel, 10);
			if (deltaArm) {
				//printf("Delta Arm is %d\n", deltaArm);
				arm->moveFourBar(deltaArm);
				arm->lockFourBar();
				//arm->setFourBarSetpoint(arm->getFourBarPosition()); // Must be here otherwise will drift
			} else {
				//printf("Four Bar setpoint is %d\n", arm->getFourBarSetpoint());
				arm->fourBarLoop(); // Simply run the PID. Do *not* update the setpoint while this is running
			}
		}

		// Move mobile goal
		if (moGoalFwd) {
			moGoal->setSetpoint(moGoal->getIME() + KMaxMotorSpeed);
		} else if(moGoalBck) {
			moGoal->setSetpoint(moGoal->getIME() - KMaxMotorSpeed);
		}
		moGoal->loop();
		//printf("Mogo IME: %d\n", moGoal->getIME()); // IME goes from 0-1750 at max +/- 20

		// Start collector
		if (cllFwd && !stackingCone) {
			arm->moveCollector(KMaxMotorSpeed); // Collector forward
		} else if(cllBck && !stackingCone) {
			arm->moveCollector(-KMaxMotorSpeed); // Collector backward
		} else {
			arm->moveCollector(0); // Stop collector
		}

		// Start stacking a cone or stop if a cone is being stacked
		if (stackCone) {
			arm->startStackingCone();
		}
		stackingCone = arm->checkStackConeTask();

		delay(DELAY_TIME); // Small delay
	}
}
