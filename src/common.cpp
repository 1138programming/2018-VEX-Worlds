#include "main.h"
#include "common.h"

int threshold(int aNumber, int threshold) {
	return (abs(aNumber) >= threshold) ? aNumber : 0;
}

bool getLimitSwitch(unsigned char pin) {
	return digitalRead(pin) == LOW;
}

int range(int value, int min, int max) {
	if (value < min)
		return min;
	else if (value > max)
		return max;
	return value;
}

float fabs(float value) {
	if(value < 0)
		return -1 * value;
	return value;
}
