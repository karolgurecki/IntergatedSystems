#ifndef _PCA9532_H_
#define _PCA9532_H_

#include <general.h>
#include <lpc2xxx.h>

#define LCD_CS     0x00000080
#define LCD_CLK    0x00000010
#define LCD_MOSI   0x00000040

void sendToLCD(tU8 firstBit, tU8 data);
void initSpiForLcd(void);
void selectLCD(tBool select);

#endif
