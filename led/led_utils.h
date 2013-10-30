/*
 * led_utils.h
 *
 *  Created on: 26-10-2013
 *      Author: embedded
 */

#ifndef LED_UTILS_H_
#define LED_UTILS_H_

#include "../startup/general.h"

tU16 determineLedDelay();

tU16 lightLedPatternOne();

static void turnLedOnAtPosition(tU8 led) {
	setPca9532Pin(led, 1);
}

static void turnLedOffAtPosition(tU8 led) {
	setPca9532Pin(led, 0);
}

#endif /* LED_UTILS_H_ */
