/*
 * motor.c
 *
 *  Created on: 30-10-2013
 *      Author: embedded
 */
#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"
#include "../startup/printf_P.h"
#include "../startup/lpc2xxx.h"
#include "motor.h"

#define MOTORROC_STACK_SIZE 300

static tU8 motorProcStack[MOTORROC_STACK_SIZE];
static tU8 motorProcPid;

static void procMotor(void* arg) {
	if (spin == TRUE) {
		printf("Motor power\n");
		static tU32 stepmotorSteps[4] = { 0x00201000, 0x00200000, 0x00000000,
				0x00001000 }; //P0.21 and P0.12 are used to contol the stepper motor
		static tU8 stepmotorIndex = 0;
		tU8 i;

		IODIR0 |= 0x00201000;
		IOCLR0 = stepmotorSteps[0];

		for (i = 0; i < 16; i++) {
			//update to new step (forward)
			stepmotorIndex = (stepmotorIndex + 1) & 0x03;

			//output new step
			IOCLR0 = stepmotorSteps[0];
			IOSET0 = stepmotorSteps[stepmotorIndex];
		}
		spin = FALSE;
	}
}

void initMotor(void){
	spin=FALSE;
	tU8 error;
		osCreateProcess(procMotor, motorProcStack, MOTORROC_STACK_SIZE, &motorProcPid, 10,
				NULL, &error);
		osStartProcess(motorProcPid, &error);

}
