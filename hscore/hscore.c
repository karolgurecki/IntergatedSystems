/*
 * hscore.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#include "hscore.h"
#include <string.h>

static tS8 buffer[512 * 1]; // sector
static FATFS fatFileSystem;
static DWORD sdStatus;
static DIR directory;
static FILINFO fileInfo;

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

static tBool initSD(void) {
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
	if (sdStatus == FR_OK)
		return TRUE;
	else
		return FALSE;
}

static tBool mountRepo(void) {
	if (initSD() == TRUE) {
		FRESULT fc;
		tU16 bytesRead = 0;
		tBool result = TRUE;

		printf("Accessing SD card and locating repository\n");

		fc = pf_open("hs.txt");
		printStatus(fc, "openFile");

		fc = pf_read(buffer, sizeof(buffer), &bytesRead);
		printStatus(fc, "readFile");
		printf("bytesRead %x\n", bytesRead);
		if (fc == FR_OK && bytesRead > 0)
			result = TRUE;
		else
			result = FALSE;

		if (result != TRUE) {
			printf("File not found  - creating\n");
		}

		if (result == TRUE) {
			printf("Initialized HSCore module\n");
		} else {
			printf("Failed to initialize HSCore module\n");
		}
		return result;
	}
	return FALSE;
}

static tBool umountRepo(void) {
	FRESULT fc = pf_mount(0);
	printStatus(fc, "umount");
	memset(&buffer[0], 0, sizeof(buffer));
	if (fc == FR_OK)
		return TRUE;
	else
		return FALSE;
}

static HSCORE getLastHScore(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	if (mountRepo() == TRUE) {
		printf("Reading LAST-SCORE\n");
		{
			tS16 i = 0;
			tS16 counter = 0;

			while (buffer[counter] != '\0') {
				counter = counter + 1;
			}

			char scoreEntry[counter];
			strncpy(scoreEntry, &buffer[i * counter], counter);

			printf("FROM BUFF[%d]=%s\n", i, scoreEntry);
		}
		printf("Read LAST-SCORE=%d", hs.score);
	}
	if (umountRepo() == TRUE) {
		printf("Device released...duhhhhh\n");
	}
	return hs;
}

static HSCORE getTop(void) {
	HSCORE hs;
	hs.player = NULL;
	hs.score = 0;
	if (mountRepo() == TRUE) {
		printf("Reading TOP-SCORE");
		printf("Read TOP-SCORE=%d", hs.score);
	}
	if (umountRepo() == TRUE) {
		printf("Device released...duhhhhh");
	}
	return hs;
}

static tBool saveHScore(tU16 score, char * player) {
	if (mountRepo() == TRUE) {

	}
	if (umountRepo() == TRUE) {
		printf("Device released...duhhhhh");
	}
	return TRUE;
}
