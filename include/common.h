#include "Constants.h"

#ifndef _COMMON_H_
#define _COMMON_H_

int threshold(int aNumber, int threshold = 20);

bool getLimitSwitch(unsigned char pin);

int range(int value, int min = -KMaxMotorSpeed, int max = KMaxMotorSpeed);

float fabs(float value);

#endif
