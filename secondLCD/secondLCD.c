/*
 * secondLCD.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */
#include "secondLCD.h"

/*****************************************************************************
 *
 * Description:
 *    xxx
 *
 ****************************************************************************/
static void
initSecondLCD(void)
{
	IODIR1 |= (LCD_DATA | LCD_E | LCD_RS);
	IOCLR1  = (LCD_DATA | LCD_E | LCD_RS);

	IODIR0 |= LCD_RW;
	IOCLR0  = LCD_RW;

  IODIR0 |= LCD_BACKLIGHT;
  IOCLR0  = LCD_BACKLIGHT;
}

/*****************************************************************************
 *
 * Description:
 *    xxx
 *
 ****************************************************************************/
static void
delay37us(void)
{
	volatile tU32 i;

//Temp test for 140 uS delay
	for(i=0; i<6*2500; i++)
    asm volatile (" nop"); //delay 15 ns x 2500 = about 37 us delay
}

/*****************************************************************************
 *
 * Description:
 *    xxx
 *
 ****************************************************************************/
static void
lcdBacklight(tU8 onOff)
{
	if (onOff == TRUE)
	  IOSET0 = LCD_BACKLIGHT;
	else
	  IOCLR0 = LCD_BACKLIGHT;
}

/*****************************************************************************
 *
 * Description:
 *    A process entry function
 *
 ****************************************************************************/
void
testLcd(void)
{
  initLCD();
	lcdBacklight(FALSE);
  osSleep(10);

  for(;;)
  {
 		lcdBacklight(TRUE);
    osSleep(50);

    //function set
    writeLCD(0, 0x30);
    osSleep(1);
    writeLCD(0, 0x30);
    delay37us();
    writeLCD(0, 0x30);
    delay37us();

    //function set
    writeLCD(0, 0x38);
    delay37us();

    //display off
    writeLCD(0, 0x08);
    delay37us();

    //display clear
    writeLCD(0, 0x01);
    osSleep(1); //actually only 1.52 mS needed

    //display control set
    writeLCD(0, 0x06);
    osSleep(1);

    //display control set
    writeLCD(0, 0x0c);
    delay37us();

    //cursor home
    writeLCD(0, 0x02);
osSleep(1);

    writeLCD(1, 'E');
    delay37us();
    writeLCD(1, 'm');
    delay37us();
    writeLCD(1, 'b');
    delay37us();
    writeLCD(1, 'e');
    delay37us();
    writeLCD(1, 'd');
    delay37us();
    writeLCD(1, 'd');
    delay37us();
    writeLCD(1, 'e');
    delay37us();
    writeLCD(1, 'd');
    delay37us();
    writeLCD(1, ' ');
    delay37us();
    writeLCD(1, 'A');
    delay37us();
    writeLCD(1, 'r');
    delay37us();
    writeLCD(1, 't');
    delay37us();
    writeLCD(1, 'i');
    delay37us();
    writeLCD(1, 's');
    delay37us();
    writeLCD(1, 't');
    delay37us();
    writeLCD(1, 's');
    delay37us();

    //move curstor to second row
    writeLCD(0, 0x80 | 0x40);
    delay37us();

    osSleep(20);
    writeLCD(1, 'L');
    osSleep(20);
    writeLCD(1, 'P');
    osSleep(20);
    writeLCD(1, 'C');
    osSleep(20);
    writeLCD(1, '2');
    osSleep(20);
    writeLCD(1, '1');
    osSleep(20);
    writeLCD(1, '4');
    osSleep(20);
    writeLCD(1, '8');
    osSleep(20);
    writeLCD(1, ' ');
    osSleep(20);
    writeLCD(1, 'E');
    osSleep(20);
    writeLCD(1, 'd');
    osSleep(20);
    writeLCD(1, 'u');
    osSleep(20);
    writeLCD(1, 'B');
    osSleep(20);
    writeLCD(1, 'o');
    osSleep(20);
    writeLCD(1, 'a');
    osSleep(20);
    writeLCD(1, 'r');
    osSleep(20);
    writeLCD(1, 'd');
    osSleep(50);

		lcdBacklight(FALSE);
    osSleep(50);
		lcdBacklight(TRUE);
    osSleep(50);
		lcdBacklight(FALSE);
    osSleep(50);
		lcdBacklight(TRUE);
    osSleep(50);
		lcdBacklight(FALSE);
    osSleep(50);
		lcdBacklight(TRUE);
    osSleep(50);
		lcdBacklight(FALSE);
    osSleep(50);

    //display clear
    writeLCD(0, 0x01);
    osSleep(1); //actually only 1.52 mS needed
  }
	lcdBacklight(FALSE);
}
