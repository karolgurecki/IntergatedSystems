#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <ea_init.h>
#include <stdlib.h>
#include "lcd/lcd.h"
#include "joystick/joystick.h"
#include "select.h"

static tMenu menu;
static tU8 cursor;

static void drawMenuCursor(void) {
	tU32 row;

	for (row = 0; row < menu.noOfChoices; row++) {
		lcdGotoxy(menu.xPos + 4, menu.yPos + 17 + (14 * row));
		if (row == cursor)
			lcdColor(menu.bgColor + 1, menu.selectedColor);
		else
			lcdColor(menu.bgColor, menu.choicesColor);

		lcdPuts(menu.pChoice[row]);
	}
}

tU8 drawMenu(tMenu newMenu) {
	tU8 anyKey;

	menu = newMenu;

	//draw boarder
	lcdRect(menu.xPos, menu.yPos, menu.xLen, menu.yLen, menu.borderColor);
	lcdRect(menu.xPos + 1, menu.yPos + 16, menu.xLen - 2, menu.yLen - 17,
			menu.bgColor);

	//write header text
	lcdGotoxy(menu.headerTextXpos, menu.yPos + 1);
	lcdColor(menu.borderColor, menu.headerColor);
	lcdPuts(menu.pHeaderText);

	//write choices
	cursor = menu.initialChoice;
	drawMenuCursor();
	//dummy call just to reset previous key strokes
	getPressedKey();

	while (1) {
		anyKey = getPressedKey();

		if (anyKey != KEY_NOTHING) {
			//select specific function
			if (anyKey == KEY_CENTER) {
				return cursor;
			}

			else if (anyKey == KEY_UP) {
				if (cursor > 0)
					cursor--;
				else
					cursor = menu.noOfChoices - 1;
				drawMenuCursor();
			}

			else if (anyKey == KEY_DOWN) {
				if (cursor < menu.noOfChoices - 1)
					cursor++;
				else
					cursor = 0;
				drawMenuCursor();
			}
		} else
			osSleep(1);
	}
}

