/*
 * secondLCD.h
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */

#ifndef SECONDLCD_H_
#define SECONDLCD_H_

#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <lpc2xxx.h>
#include <consol.h>
#include "../snake.h"

#define LCD_DATA      0x00ff0000  //P1.16-P1.23
#define LCD_E         0x02000000  //P1.25
#define LCD_RW        0x00400000  //P0.22
#define LCD_RS        0x01000000  //P1.24
#define LCD_BACKLIGHT 0x40000000  //P0.30
tS32 highScore;
void initSecondLCD(void);
static void delay37us(void);
static void lcdBacklight(tU8 onOff);
static void writeLCD(tU8 reg, tU8 data);
static void getScoreAsString(tU32);
static void getHSAsString();
void addTime();
void displayScoreAndTime(tU32);
void resetTime();


#endif /* SECONDLCD_H_ */
