/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  // Get instacnes of subsystems
  Arm* arm = Arm::getInstance();
  MobileGoal* mogo = MobileGoal::getInstance();
  Base* base = Base::getInstance();

  int startTime;

  base->resetEncoders();

  // Auton
  arm->setFourBarSetpoint((int)(fourBarRotationTicks * 1.38));
  while (!arm->fourBarAtSetpoint()) {
    arm->wristLoop();
    arm->fourBarLoop();
    delay(DELAY_TIME);
  }

  base->setLeftSetpoint(base->getLeftSetpoint() + 360);
  base->setRightSetpoint(base->getRightSetpoint() + 360);
  while (!base->leftAtSetpoint() || !base->rightAtSetpoint()) {
    arm->wristLoop();
    base->loopLeft();
    base->loopRight();
    //printf("Left IME is %d and right IME is %d\n", base->getLeftIME(), base->getRightIME());
    delay(DELAY_TIME);
  }
  base->lockLeft();
  base->lockRight();

  arm->setWristSetpoint((int)(wristRotationTicks * -0.25));
  while (!arm->wristAtSetpoint()) {
    arm->wristLoop();
    base->loopLeft();
    base->loopRight();
    printf("Wrist IME is %d and wrist setpoint is %d\n", arm->getWristPosition(), arm->getWristSetpoint());
    delay(DELAY_TIME);
  }
  arm->lockWrist();

  /*startTime = millis();
  while (millis() - startTime > 2000) {
    arm->moveCollector(-127);
    arm->wristLoop();
    base->loopLeft();
    base->loopRight();
    delay(DELAY_TIME);
  }

  arm->setWristSetpoint(0);
  while (!arm->wristAtSetpoint()) {
    arm->wristLoop();
    base->loopLeft();
    base->loopRight();
    delay(DELAY_TIME);
  }
  arm->lockWrist();
  arm->moveCollector(0);*/

  /*arm->moveWrist(-100);
  delay(800);
  arm->moveWrist(0);

  arm->moveCollector(-127);
  delay(1000);

  arm->moveWrist(100);
  delay(1000);
  arm->moveWrist(0);

  arm->moveCollector(0);*/

  // Get robot ready for teleop
  /*mogo->moveMobileGoal(127);
  delay(130);
  mogo->moveMobileGoal(0);
  mogo->resetIME();
  arm->lockFourBar();*/
}
