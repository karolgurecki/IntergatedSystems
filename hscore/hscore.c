/*
 * hscore.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#include "hscore.h"

tU8 buffer[512 * 1]; // sector

static tBool initHScore(void) {
	printf("Initializing HSCore module");
	FRESULT fc;
	tU16 bytesRead = 0;
	tBool result = TRUE;

	printf("Accessing SD card and locating repository\n");
	fc = pf_read(buffer, sizeof(buffer), &bytesRead);
	printf("Result is %x\n", fc);

	if (fc || !bytesRead) {
		printf("File not found  - creating\n");
	}

	if (result == TRUE) {
		printf("Initialized HSCore module\n");
	} else {
		printf("Failed to initialize HSCore module\n");
	}
	return result;
}

static HSCORE getLastHScore(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	return hs;
}

static HSCORE getTop(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	return hs;
}

static tBool saveHScore(tU16 score, char * player) {
	return TRUE;
}
