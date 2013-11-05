/*
 * hscore.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#include "hscore.h"

tU8 buffer[512 * 1]; // sector

tBool initHScore(void) {
	printf("Initializing HSCore module");
	FRESULT fc;
	tU16 bytesRead = 0;
	tBool result = TRUE;

	printf("Accessing SD card and locating repository");
	fc = pf_read(buffer, sizeof(buffer), &bytesRead);
	printf("Result is %x", fc);

	if (fc || !bytesRead) {
		printf("File not found  - creating");
	}

	if (result == TRUE) {
		printf("Initialized HSCore module");
	} else {
		printf("Failed to initialize HSCore module");
	}
	return result;
}

HSCORE getLastHScore(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	return hs;
}

HSCORE getTop(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	return hs;
}

tBool saveHScore(tU16 score, char * player) {
	return TRUE;
}
