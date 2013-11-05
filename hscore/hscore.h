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
	char *player;
} HSCORE;

static void initSD(void);
static void printStatus(FRESULT, const char *);
static tBool initHScore(void);
static HSCORE getLastHScore(void);
static HSCORE getTop(void);
static tBool saveHScore(tU16 score, char * player);

#endif /* HSCORE_H_ */
