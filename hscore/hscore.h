/*
 * hscore.h
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#ifndef HSCORE_H_
#define HSCORE_H_

#include "../sd/pff.h"
#include "../startup/general.h"

typedef struct {
	tU16 score;
	char player[10];
} HSCORE;

HSCORE getLastHScore(void);
tBool saveHScore(tS32 score, char * player);

#endif /* HSCORE_H_ */
