/*
 * secondLCD.c
 *
 *  Created on: 05-11-2013
 *      Author: embedded
 */
#include "secondLCD.h"
tU8 scoreString[16];
tU8 timeString[16];
volatile tU32 time;

void initSecondLCD(void) {
	IODIR1 |= (LCD_DATA | LCD_E | LCD_RS);
	IOCLR1 = (LCD_DATA | LCD_E | LCD_RS);

	IODIR0 |= LCD_RW;
	IOCLR0 = LCD_RW;

	IODIR0 |= LCD_BACKLIGHT;
	IOCLR0 = LCD_BACKLIGHT;
}

static void delay37us(void) {
	volatile tU32 i;

	//Temp test for 140 uS delay
	for (i = 0; i < 6 * 2500; i++)
		asm volatile (" nop");
	//delay 15 ns x 2500 = about 37 us delay
}

static void lcdBacklight(tU8 onOff) {
	if (onOff == TRUE)
		IOSET0 = LCD_BACKLIGHT;
	else
		IOCLR0 = LCD_BACKLIGHT;
}

static void writeLCD(tU8 reg, tU8 data) {
	volatile tU8 i;

	if (reg == 0)
		IOCLR1 = LCD_RS;
	else
		IOSET1 = LCD_RS;

	IOCLR0 = LCD_RW;
	IOCLR1 = LCD_DATA;
	IOSET1 = ((tU32) data << 16) & LCD_DATA;
	//printf("\nwrite: %x", data);
	IOSET1 = LCD_E;
	//	osSleep(1);
	for (i = 0; i < 16; i++)
		asm volatile (" nop");
	//delay 15 ns x 16 = about 250 ns delay
	IOCLR1 = LCD_E;
	//	osSleep(1);
	for (i = 0; i < 16; i++)
		asm volatile (" nop");
	//delay 15 ns x 16 = about 250 ns delay
}

static void getScoreAsString(tU32 score) {
	int i;
	for (i = 0; i < 16; i++) {
		scoreString[i] = ' ';
	}
	scoreString[0] = 'S';
	scoreString[1] = 'c';
	scoreString[2] = 'o';
	scoreString[3] = 'r';
	scoreString[4] = 'e';
	scoreString[5] = ':';
	scoreString[6] = score / 100000 + '0';
	scoreString[7] = (score / 10000) % 10 + '0';
	scoreString[8] = (score / 1000) % 10 + '0';
	scoreString[9] = (score / 100) % 10 + '0';
	scoreString[10] = (score / 10) % 10 + '0';
	scoreString[11] = score % 10 + '0';
	scoreString[12] = 0;

	//remove leading zeroes
	if (scoreString[6] == '0') {
		scoreString[6] = ' ';
		if (scoreString[7] == '0') {
			scoreString[7] = ' ';
			if (scoreString[8] == '0') {
				scoreString[8] = ' ';
				if (scoreString[9] == '0') {
					scoreString[9] = ' ';
					if (scoreString[10] == '0') {
						scoreString[10] = ' ';
					}
				}
			}
		}
	}
}

static void getTimeAsString() {
	int i;
	for (i = 0; i < 16; i++) {
		timeString[i] = ' ';
	}
	timeString[0] = 'T';
	timeString[1] = 'i';
	timeString[2] = 'm';
	timeString[3] = 'e';
	timeString[4] = '[';
	timeString[5] = 's';
	timeString[6] = ']';
	timeString[7] = ':';
	timeString[8] = time / 100000 + '0';
	timeString[9] = (time / 10000) % 10 + '0';
	timeString[10] = (time / 1000) % 10 + '0';
	timeString[11] = (time / 100) % 10 + '0';
	timeString[12] = (time / 10) % 10 + '0';
	timeString[13] = time % 10 + '0';
	timeString[14] = 0;

	//remove leading zeroes
	if (timeString[8] == '0') {
		timeString[8] = ' ';
		if (timeString[9] == '0') {
			timeString[9] = ' ';
			if (timeString[10] == '0') {
				timeString[10] = ' ';
				if (timeString[11] == '0') {
					timeString[11] = ' ';
					if (timeString[12] == '0') {
						timeString[12] = ' ';
					}
				}
			}
		}
	}
}
void displayScoreAndTime(tU32 score) {
	lcdBacklight(TRUE);
	printf("Display score %d\n", score);
	getScoreAsString(score);
	getTimeAsString();
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

	printf("%s\n",scoreString);

	int i;
	for (i = 0; i < 16; i++) {
		if (scoreString[i] != ' ') {
			writeLCD(1, scoreString[i]);
			delay37us();
		}
	}

	//move curstor to second row
	writeLCD(0, 0x80 | 0x40);
	delay37us();

	printf("%s\n",timeString);

	for (i = 0; i < 14; i++) {
		if (timeString[i] != ' ') {
			writeLCD(1, timeString[i]);
			delay37us();
		}
	}
}

void addTime() {
	time = time + 1;
}

void resetTime() {
	time = 0;
}
