/*
 * hscore.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#include "hscore.h"

static tU8 buffer[512 * 1]; // sector

static void initSD(void) {
	printf("=>SD mounting...\n");
	sdStatus = pf_mount(&fatFileSystem);
	if (sdStatus) {
		printf("Failed to mount SD");
		if (FR_DISK_ERR == sdStatus || FR_NOT_READY == sdStatus) {
			printf("SD not ready...\n");
		} else if (FR_NO_FILESYSTEM == sdStatus) {
			printf("File system error...\n");
		}
	} else {
		if (sdStatus == FR_OK) {
			printf("SD ready... :)\n");
		}
	}
}

static void printStatus(FRESULT fc, const char *action) {
	switch (fc) {
	case FR_OK:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_OK");
		break;
	case FR_DISK_ERR:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_DISK_ERR");
		break;
	case FR_NOT_READY:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NOT_READY");
		break;
	case FR_NO_FILE:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NO_FILE");
		break;
	case FR_NO_PATH:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NO_PATH");
		break;
	case FR_NOT_OPENED:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NOT_OPENED");
		break;
	case FR_NOT_ENABLED:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NOT_ENABLED");
		break;
	case FR_NO_FILESYSTEM:
		printf("SD[action=%s =>> status=%s]\n", action, "FR_NO_FILESYSTEM");
		break;
	}
}

static tBool initHScore(void) {
	FRESULT fc;
	tU16 bytesRead = 0;
	tBool result = TRUE;

	printf("Accessing SD card and locating repository\n");

	fc = pf_open("hs.txt");
	printStatus(fc, "openFile");

	fc = pf_read(buffer, sizeof(buffer), &bytesRead);
	printStatus(fc, "readFile");

	result = fc == FR_OK && bytesRead > 0;

	if (result != 1) {
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
