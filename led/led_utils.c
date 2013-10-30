/*
 * led_utils.c
 *
 *  Created on: 30-10-2013
 *      Author: embedded
 */
#include "led_utils.h"

tU16 determineLedDelay() {
	tU8 pca9532Present = FALSE;
	tU16 led_delay = 0;

	//check if connection with PCA9532
	pca9532Present = pca9532Init();

	if (pca9532Present) {
		led_delay = 10;
	} else {
		led_delay = 0;
	}
	return led_delay;
}
tU16 lightLedPatternOne() {

	tU16 led_delay = determineLedDelay();

	setPca9532Pin(0, 0);
	setPca9532Pin(15, 0);
	osSleep(led_delay);
	setPca9532Pin(1, 0);
	setPca9532Pin(14, 0);
	osSleep(led_delay);
	setPca9532Pin(2, 0);
	setPca9532Pin(13, 0);
	osSleep(led_delay);
	setPca9532Pin(3, 0);
	setPca9532Pin(12, 0);
	osSleep(led_delay);
	setPca9532Pin(4, 0);
	setPca9532Pin(11, 0);
	osSleep(led_delay);
	setPca9532Pin(5, 0);
	setPca9532Pin(10, 0);
	osSleep(led_delay);
	setPca9532Pin(6, 0);
	setPca9532Pin(9, 0);
	osSleep(led_delay);
	setPca9532Pin(7, 0);
	setPca9532Pin(8, 0);
	osSleep(led_delay);
	setPca9532Pin(0, 1);
	setPca9532Pin(1, 1);
	setPca9532Pin(2, 1);
	setPca9532Pin(3, 1);
	setPca9532Pin(4, 1);
	setPca9532Pin(5, 1);
	setPca9532Pin(6, 1);
	setPca9532Pin(7, 1);
	setPca9532Pin(8, 1);
	setPca9532Pin(9, 1);
	setPca9532Pin(10, 1);
	setPca9532Pin(11, 1);
	setPca9532Pin(12, 1);
	setPca9532Pin(13, 1);
	setPca9532Pin(14, 1);
	setPca9532Pin(15, 1);
	osSleep(2);

	return ~getPca9532Pin();
}
