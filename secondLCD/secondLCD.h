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

#define LCD_DATA      0x00ff0000  //P1.16-P1.23
#define LCD_E         0x02000000  //P1.25
#define LCD_RW        0x00400000  //P0.22
#define LCD_RS        0x01000000  //P1.24
#define LCD_BACKLIGHT 0x40000000  //P0.30



#endif /* SECONDLCD_H_ */
