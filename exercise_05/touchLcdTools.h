#ifndef TOUCH_LCD_TOOLS_H

#include "LCD_DISCO_F469NI.h"
#include "mbed.h"

#define TOUCH_LCD_TOOLS_H

#define TOUCH_LCD_DISPLAY_TIMER_REFRESH_FREQUENCY_MILLISECONDS 100
#define TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION 1

#define TOUCH_LCD_DISPLAY_BUTTONS_COUNT 3
#define TOUCH_LCD_DISPLAY_BUTTONS_COLORS { LCD_COLOR_RED, LCD_COLOR_GREEN, LCD_COLOR_BLUE }

void initTouchDisplay();
void exitTouchDisplay();
static void initTouchDisplayButtons();

void initTouchDisplayTimer();
static void updateTouchDisplayTimerState();

static int* generateExplosionEventsFlagsRandomizedIndeces(); 
static int* generateTouchDisplayButtonsBoundaries();
void checkForTouchEvent();

void activateTouchDisplayGetJinxedMode();
void resetTouchDisplayTimer();
void stopTouchDisplayTimer();

#endif