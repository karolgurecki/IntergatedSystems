#ifndef _SELECT_H_
#define _SELECT_H_

#include "../pre_emptive_os/api/general.h"

typedef struct {
	tU8 xPos;
	tU8 yPos;
	tU8 xLen;
	tU8 yLen;
	tU8 noOfChoices;
	tU8 initialChoice;
	tU8 *pHeaderText;
	tU8 headerTextXpos;
	tU8 *pChoice[6];
	tU8 bgColor;
	tU8 borderColor;
	tU8 headerColor;
	tU8 choicesColor;
	tU8 selectedColor;
} tMenu;

tU8 drawMenu(tMenu newMenu);

#endif
