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

  // Auton
  /*arm->moveFourBar(127);
  delay(550);
  arm->moveFourBar(0);*/
  arm->setFourBarSetpoint((int)(fourBarRotationTicks * 1.4));
  //base->setReference();
  base->setLeftSetpoint(base->getLeftSetpoint() + 360);
  base->setRightSetpoint(base->getRightSetpoint() + 360);
  while (!arm->fourBarAtSetpoint()) {
    arm->fourBarLoop();
    //base->moveBaseTo(360);
    base->loopLeft();
    base->loopRight();
    //printf("Four bar setpoint is %d and four bar position is %d\n", arm->getFourBarSetpoint(), arm->getFourBarPosition());
    printf("Base imes are %d and %d\n", base->getLeftIME(), base->getRightIME());
    delay(DELAY_TIME);
  }

  while(!base->leftAtSetpoint() || !base->rightAtSetpoint()) {
    delay(DELAY_TIME);
  }

  int startTime = millis();
  while(millis() - startTime < 500) {
    arm->moveCollector(-KMaxMotorSpeed);
  }

  // Get robot ready for teleop
  mogo->moveMobileGoal(127);
  delay(130);
  mogo->moveMobileGoal(0);
  mogo->resetIME();
  arm->lockFourBar();
}
