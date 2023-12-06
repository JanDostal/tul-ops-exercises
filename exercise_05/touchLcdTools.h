#ifndef TOUCH_LCD_TOOLS_H

#include "LCD_DISCO_F469NI.h"
#include "mbed.h"

#define TOUCH_LCD_TOOLS_H

#define TOUCH_LCD_DISPLAY_TIMER_REFRESH_FREQUENCY_MILLISECONDS 100
#define TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION 1

#define TOUCH_LCD_DISPLAY_BUTTONS_COUNT 3
#define TOUCH_LCD_DISPLAY_BUTTONS_COLORS { LCD_COLOR_RED, LCD_COLOR_GREEN, LCD_COLOR_BLUE }

typedef struct
{
	int* explosionEventsFlagsRandomizedIndeces;
    int* touchDisplayButtonsBoundaries;
} TOUCH_DISPLAY_BUTTONS_DATA, * TOUCH_DISPLAY_BUTTONS_DATA_REFERENCE;

TOUCH_DISPLAY_BUTTONS_DATA_REFERENCE initTouchDisplay();
void exitTouchDisplay();

static int* generateExplosionEventsFlagsRandomizedIndeces(); 
static int* generateTouchDisplayButtonsBoundaries();
static TOUCH_DISPLAY_BUTTONS_DATA_REFERENCE initTouchDisplayButtons();

void initTouchDisplayTimer();
static void updateTouchDisplayTimerState();

void checkForTouchEvent(TOUCH_DISPLAY_BUTTONS_DATA_REFERENCE buttonsDataReference);

void activateTouchDisplayGetJinxedMode();
void resetTouchDisplayTimer();
void stopTouchDisplayTimer();

#endif