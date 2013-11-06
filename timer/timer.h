#ifndef TIMER_H
#define TIMER_H
/*
 This file declares used to pause program for desire amount of miliseconds.
*/

#include "../startup/lpc2xxx.h"
#include "inttypes.h"
#include "../startup/config.h"
#include "../startup/general.h"


//some timer parameters
#define CRYSTAL_FREQUENCY FOSC
#define PLL_FACTOR        PLL_MUL
#define VPBDIV_FACTOR     PBSD


//zatrzymaj program na okre�lon� ilo�� mikrosekund
void sleep(tU32 delayInUs);

#endif
