/*
 * hscore.h
 *
 * HScore is a module which is designed
 * to do 2 operations over the file located in the SD
 * file. It uses PETIT-FS framework which eases with
 * developing the code responsible for IO operations
 * on the SD card.
 *
 *  Created on: 05-11-2013
 *      Author: t.trebski
 */

#ifndef HSCORE_H_
#define HSCORE_H_

#include "../sd/pff.h"
#include "../startup/general.h"

/**
 * HSCORE is the class like structure which defines the information about the read hscore.
 */
typedef struct {
	tU16 score;
	char player[10];
} HSCORE;

/**
 * Retrieves the HSCore struct by executing following operations:
 * 1. mounting the repository (the file)
 * 2. reading file content into the buffer
 * 3. splitting read line by = character
 * 4. constructing hscore struct
 * 5. umounting the Repository
 * 6. returing HSCore instance
 */
HSCORE getLastHScore(void);

/**
 * DOES NOT WORK:
 *
 * This mention intended to save the hscore to the file.
 * However due to inability to implement this functionality
 * with *PETIT-FS* it is not working
 */
tBool saveHScore(tS32 score, char * player);

#endif /* HSCORE_H_ */
