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
extern int imeCount;

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
	/*printf("Beginning op controler\n");

	Motor* port2 = Motor::getMotor(2);
	Motor* port3 = Motor::getMotor(3);

	port2->addFollower(port3);

	PIDController* controller = new PIDController(port2, 0.1, 0.0, 0.01);

	Encoder encoder = encoderInit(12, 11, true);

	controller->setSetpoint(3600);

	while (true) {
		//printf("Motor port is %d\n", port2->getChannel());
		int count = encoderGet(encoder);
		//printf("IME value is %d\n", count);
		controller->sensorValue(count);
		controller->loop();
		delay(DELAY_TIME);
	}*/

	//Define joystick input variables
	int leftSide, rightSide, wristChannel, fourBarChannel; // Joysticks channel values
	bool moGoalFwd, moGoalBck, stackCone, cllFwd, cllBck, slowMode = false; // Button states
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
	/*moGoal->moveMobileGoal(127);
  delay(130);
  moGoal->moveMobileGoal(0);
  moGoal->resetIME();*/
	arm->lockFourBar();

	/*while(true) {
		moGoalFwd = joystickGetDigital(1, 5, JOY_DOWN);
		moGoalBck = joystickGetDigital(1, 5, JOY_UP);
		if (moGoalFwd) {
			//moGoal->setSetpoint(moGoal->getIME() + KMaxMotorSpeed);
			printf("Mobile goal forward\n");
			//moGoal->moveMobileGoal(KMaxMotorSpeed);
			arm->moveFourBar(KMaxMotorSpeed);
		} else if(moGoalBck) {
			//moGoal->setSetpoint(moGoal->getIME() - KMaxMotorSpeed);
			printf("Mobile goal backward\n");
			//moGoal->moveMobileGoal(-KMaxMotorSpeed);
			arm->moveFourBar(-KMaxMotorSpeed);
		}
	}*/

  /*while (true) {
    arm->moveWrist(KMaxMotorSpeed);
    printf("Wrist IME is %d\n", arm->getWristPosition());
  }*/

  // if (true) {
	// 	printf("Starting auton\n");
	// 	autonomous();
	// }

	while (true) {
		// Set joysticks
		leftSide = joystickGetAnalog(1, 3); // Left y-channel
		rightSide = joystickGetAnalog(1, 2); // Right y-channel
		wristChannel = joystickGetAnalog(2, 3); // Left y-channel
		fourBarChannel = joystickGetAnalog(2, 2); // Right y-channel

		// Set buttons
		moGoalFwd = joystickGetDigital(1, 6, JOY_DOWN);
		moGoalBck = joystickGetDigital(1, 6, JOY_UP);
		cllFwd = joystickGetDigital(2, 6, JOY_DOWN);
		cllBck = joystickGetDigital(2, 6, JOY_UP);
		/*stackCone = joystickGetDigital(2, 8, JOY_LEFT);
		if (stackCone) {
			// Don't do the action multiple times and leave us in an undefined state
			while (joystickGetDigital(2, 8, JOY_LEFT)) {
				delay(DELAY_TIME);
			}
		}*/
		stackCone = false;
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
			// Move the wrist - New 4/23: Added code to check if IME is present or not. If it isn't fall back to non-PID code
			deltaWrist = threshold(wristChannel, 20);
			if (imeCount < 4) {
				//printf("Less that 4 imes? %d\n", imeCount);
				arm->moveWrist(deltaWrist);
			} else {
				/*if (deltaWrist) {
					arm->moveWrist(deltaWrist);
					arm->lockWrist();
					//arm->setWristSetpoint(arm->getWristPosition());
				} else {
					//arm->moveWrist(0);
					arm->wristLoop();
				}
				printf("Delta wrist is %d, wrist IME is %d and wrist setpoint is %d\n", deltaWrist, arm->getWristPosition(), arm->getWristSetpoint());*/
				arm->moveWrist(deltaWrist);
				//printf("Wrist encoder value: %d\n", arm->getWristPosition());
			}
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
		//printf("Mobile goal position is %d\n", moGoal->getPosition());
		//printf("Mobile goal forward button %d and mobile goal backward button %d\n", moGoalFwd, moGoalBck);
		//printf("Mobile setpoint is %d\n", moGoal->getSetpoint());
		if (moGoalFwd) {
			moGoal->setSetpoint(moGoal->getIME() + KMaxMotorSpeed);
			//moGoal->moveMobileGoal(KMaxMotorSpeed);
		} else if(moGoalBck) {
			moGoal->setSetpoint(moGoal->getIME() - KMaxMotorSpeed);
			//moGoal->moveMobileGoal(-KMaxMotorSpeed);
		} else {
			moGoal->lock();
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
