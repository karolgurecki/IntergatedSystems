#ifndef TIMER_H
#define TIMER_H

#include "../startup/lpc2xxx.h"
#include "inttypes.h"
#include "../startup/config.h"
#include "../startup/general.h"


#define CRYSTAL_FREQUENCY FOSC
#define PLL_FACTOR        PLL_MUL
#define VPBDIV_FACTOR     PBSD


void sleep(tU32 delayInUs);

#endif
