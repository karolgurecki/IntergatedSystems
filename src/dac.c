#include "dac.h"
#include "startup/lpc2xxx.h"


/**
 * Method activates the DAC (digital-analog converter) which in our case is used to ease
 * with speaker dev
 */
void initDac(void){
	PINSEL1 = 1<<19;
}
