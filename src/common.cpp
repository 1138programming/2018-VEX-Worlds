#include "main.h"
#include "common.h"

int threshold(int aNumber, int threshold) {
	return (abs(aNumber) >= threshold) ? aNumber : 0;
}

bool getLimitSwitch(unsigned char pin) {
	return digitalRead(pin) == LOW;
}
