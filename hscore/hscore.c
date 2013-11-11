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

	if (mountRepo() == TRUE) {
		printf("HSCORE => Reading LAST-SCORE\n");
		{
			tS16 i = 0;
			tS16 counter = 0;

			char scoreEntry[100];
			strncpy(scoreEntry, &buffer[0], sizeof(buffer));

			printf("HSCORE => FROM BUFF[%d]=%s\n", i, scoreEntry);

			char * pch = strtok(scoreEntry, "=");
			i = 0;
			while (pch != NULL ) {
				if (i == 0) {
					/////////////////////////////////
					counter = 0;
					while (pch[counter] != '\0') {
						counter = counter + 1;
					}
					strncpy(hs.player, &pch[0], sizeof(pch));
					hs.player[strlen(hs.player)] = '\0';
					/////////////////////////////////
				} else if (i == 1) {
					hs.score = atoi(pch);
				}
				pch = strtok(NULL, "=");
				i++;
			}
		}
		printf("HSCORE => LAST-SCORE > Player=%s > Score=%d\n", hs.player,
				hs.score);
	}

	if (umountRepo() == TRUE) {
		printf("HSCORE => Device released...duhhhhh\n");
	}
	return hs;
}

static tBool saveHScore(tS32 score, char * player) {
	if (mountRepo() == TRUE) {
		FRESULT fc;
		tU16 bitesWritten = 0;
		union {
			int x;
			char ch[sizeof(int)];
		} u;

		printf("Accessing SD card and locating repository\n");

		fc = pf_open("hs.txt");
		printStatus(fc, "openFile");

		memset(&buffer[0], 0, sizeof(buffer));
		char str[100];
		strncat(str, player, sizeof(player));

		u.x = score;
		strcat(str, "=");
		strncat(str, u.ch, sizeof(u.ch));

		fc = pf_write(str, sizeof(str), &bitesWritten);
		printStatus(fc, "writeFile");
		printf("bytesWritten %x\n", bitesWritten);
	}
	if (umountRepo() == TRUE) {
		printf("Device released...duhhhhh");
	}
	return TRUE;
}
