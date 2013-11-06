#include "dac.h"
#include "startup/lpc2xxx.h"


void initDac(void){
	// Aktywuje P0.25. Bit 19-ty jest odpowiedzialny za Aout(DAC)
	// czyli wyjœcie analogowe przetwornik cyrfowo analogowego.
	// w³¹czenie zatem polega tylko na w³¹czeniu pinu
	PINSEL1 = 1<<19;
}
