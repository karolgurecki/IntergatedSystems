/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2008 Embedded Artists AB
 *
 * Description:
 *    Main program for Experiment Expansion Board (for LPC2103 Education Board)
 *
 *****************************************************************************/

#include "pre_emptive_os/api/osapi.h"
#include "pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <ea_init.h>
#include <lpc2xxx.h>
#include <consol.h>
#include "i2c/i2c.h"
#include "adc/adc.h"
#include "lcd/lcd.h"
#include "pca9532.h"
#include "led/led_utils.h"
#include "sd/sd.h"

#include "snake.h"
#include "key.h"

#include "graphics/fire_0_100x40c.h"
#include "graphics/fire_1_100x40c.h"
#include "graphics/fire_2_100x40c.h"
#include "graphics/fire_3_100x40c.h"
#include "graphics/fire_4_100x40c.h"

#define SPI_SLAVE_CS 0x00002000  //pin P0.13
#define ENC_RESET    0x00001000  //pin P0.12
#define FAILSAFE_VALUE 5000

#define PROC1_STACK_SIZE 750
#define PROC2_STACK_SIZE 750
#define INIT_STACK_SIZE  400

static tU8 gameProcessStack[PROC1_STACK_SIZE];
static tU8 ledsStack[PROC2_STACK_SIZE];
static tU8 tkSnakeStack[INIT_STACK_SIZE];
static tU8 pid1;
static tU8 pid2;
static tU16 globalKeys;

static void initializeGameProcess(void* arg);
static void initializeLEDs(void* arg);
static void initializeTKSnake(void* arg);

/*****************************************************************************
 * Global variables
 ****************************************************************************/
volatile tU32 ms;
static tU8 contrast = 46;

/**
 * Entry procedure.
 * Call order:
 * 1. initialize OS -> osInit();
 * 2. create the process by passing callback method which actually creates our app as the first argument
 * 3. start the process
 * 4. start OS
 */
int main(void) {
	tU8 error = 0;
	tU8 pid = 0;

	osInit();
	osCreateProcess(initializeTKSnake, tkSnakeStack, INIT_STACK_SIZE, &pid, 1,
			NULL, &error);
	osStartProcess(pid, &error);

	osStart();
	return 0;
}

/*****************************************************************************
 *
 * Description:
 *    Draw main menu
 *
 ****************************************************************************/
static void drawMenu(void) {
	lcdColor(0, 0);
	lcdClrscr();

	lcdRect(14, 0, 102, 128, 0x6d);
	lcdRect(15, 17, 100, 110, 0);

	lcdGotoxy(48, 1);
	lcdColor(0x6d, 0);
	lcdPuts("MENU");

	for (int i = 1; i <= 2; i++) {
		lcdGotoxy(22, 20 + (14 * i));
		lcdColor(0x00, 0xE0);
		switch (i) {
		case 1:
			lcdPuts("Play");
			break;
		case 2:
			lcdPuts("High Score");
			break;
		}
	}
}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void initializeGameProcess(void* arg) {
	static tU8 i = 0;

	IODIR |= 0x00006000;  //P0.13/14
	IOSET = 0x00006000;

	lcdInit();
	initKeyProc();
	drawMenu();
	lcdContrast(contrast);

	while (TRUE) {
		tU8 anyKey;

		anyKey = checkKey();
		if (anyKey != KEY_NOTHING) {
			//select specific function
			if (anyKey == KEY_CENTER) {
				playSnake();
				drawMenu();
			}

			//adjust contrast
			else if (anyKey == KEY_RIGHT) {
				contrast++;
				if (contrast > 127)
					contrast = 127;
				lcdContrast(contrast);
			} else if (anyKey == KEY_LEFT) {
				if (contrast > 0)
					contrast--;
				lcdContrast(contrast);
			}
		}

		switch (i) {
		case 0:
			lcdIcon(15, 88, 100, 40, _fire_0_100x40c[2], _fire_0_100x40c[3],
					&_fire_0_100x40c[4]);
			i++;
			break;
		case 1:
			lcdIcon(15, 88, 100, 40, _fire_1_100x40c[2], _fire_1_100x40c[3],
					&_fire_1_100x40c[4]);
			i++;
			break;
		case 2:
			lcdIcon(15, 88, 100, 40, _fire_2_100x40c[2], _fire_2_100x40c[3],
					&_fire_2_100x40c[4]);
			i++;
			break;
		case 3:
			lcdIcon(15, 88, 100, 40, _fire_3_100x40c[2], _fire_3_100x40c[3],
					&_fire_3_100x40c[4]);
			i++;
			break;
		case 4:
			lcdIcon(15, 88, 100, 40, _fire_4_100x40c[2], _fire_4_100x40c[3],
					&_fire_4_100x40c[4]);
			i = 0;
			break;
		default:
			i = 0;
			break;
		}
		osSleep(20);
	}
}

static void initializeLEDs(void* arg) {
	while (TRUE) {
		globalKeys = lightLedPatternOne();
	}
}

/**
 * Initializes TKSnake
 * Call order:
 * 1. initialize out stream (printf)
 * 2. initialize i2c interface
 * 3. Bootstraps two process [main app, led pattern]
 */
static void initializeTKSnake(void* arg) {
	tU8 error;

	eaInit();
	i2cInit();
	initSD();

	osCreateProcess(initializeGameProcess, gameProcessStack, PROC1_STACK_SIZE,
			&pid1, 3, NULL, &error);
	osStartProcess(pid1, &error);

	osCreateProcess(initializeLEDs, ledsStack, PROC2_STACK_SIZE, &pid2, 3, NULL,
			&error);
	osStartProcess(pid2, &error);

	osDeleteProcess();
}

/*****************************************************************************
 *
 * Description:
 *    The timer tick entry function that is called once every timer tick
 *    interrupt in the RTOS. Observe that any processing in this
 *    function must be kept as short as possible since this function
 *    execute in interrupt context.
 *
 * Params:
 *    [in] elapsedTime - The number of elapsed milliseconds since last call.
 *
 ****************************************************************************/
void appTick(tU32 elapsedTime) {
	ms += elapsedTime;
}
