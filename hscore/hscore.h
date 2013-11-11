/*
 * hscore.h
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#ifndef HSCORE_H_
#define HSCORE_H_

#include "../startup/general.h"
#include "../startup/consol.h"
#include "../startup/printf_P.h"
#include "../sd/pff.h"

typedef struct {
	tU16 score;
	char player[10];
} HSCORE;

static void printStatus(FRESULT, const char *);
static tBool initSD(void);
static tBool mountRepo(void);
static tBool umountRepo(void);
static HSCORE getLastHScore(void);
static tBool saveHScore(tS32 score, char * player);

#endif /* HSCORE_H_ */
