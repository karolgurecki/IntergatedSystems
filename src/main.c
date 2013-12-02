/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2008 Embedded Artists AB
 *
 * Description:
 *    Main program for Experiment Expansion Board (for LPC2103 Education Board)
 *
 *****************************************************************************/

#include "startup/ea_init.h"
#include "startup/lpc2xxx.h" //definicje
#include "startup/config.h"

#include "i2c/i2c.h"
#include "lcd/lcd.h"
#include "pca9532.h"
#include "snake.h"
#include "joystick/joystick.h"
#include "timer/timer.h"
#include "hscore/hscore.h"
#include "secondLCD/secondLCD.h"
#include "dac.h"
#include "led/led_utils.h"

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
static tU8 contrast = 46;

static void leds(void* arg);
static void initializeGameProcess(void* arg);
static void initializeTKSnake(void* arg);

volatile tU32 ms;
// SD status variables


/**
 * Entry procedure.
 * Call order:
 * 1. initialize OS -> osInit();
 * 2. cceate the process by passing callback method which actually creates our app as the first argument
 * 3. start the process
 * 4. start OS
 */
int main(void) {
	tU8 error;
	tU8 pid;

	osInit();
	{
		osCreateProcess(initializeTKSnake, tkSnakeStack, INIT_STACK_SIZE, &pid,
				1, NULL, &error);
		osStartProcess(pid, &error);

	}
	osStart();

	return 0;
}

static void leds(void* arg) {
	while (TRUE)
		lightLedPatternOne();
}
static void initializeGameProcess(void* arg) {
	IODIR |= 0x00006000; //P0.13/14
	IOSET = 0x00006000;

	lcdInit();
	initKeyProc();
	lcdContrast(contrast);
	initSecondLCD();
	initDac();
	highScore = getLastHScore().score;

	playSnake();
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

	osCreateProcess(initializeGameProcess, gameProcessStack, PROC1_STACK_SIZE,
			&pid1, 3, NULL, &error);
	osStartProcess(pid1, &error);

	osCreateProcess(leds, ledsStack, PROC2_STACK_SIZE, &pid2, 4, NULL, &error);
	osStartProcess(pid2, &error);

	osDeleteProcess();

}

void appTick(tU32 elapsedTime) {
	ms += elapsedTime;
}
