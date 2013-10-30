#include "timer.h"

void waitFor(tU16 time) {
	while ((time--) > 0) {
		turnLedOnAtPosition(4);
		delay(0x100000);
		turnLedOffAtPosition(4);
		delay(0x100000);
	}
}

void delay(tU16 delay) {
	tU16 i = 0;
	for (i = 0; i <= delay; i++) {
	};
}
