#ifndef LCD_TOOLS_H

#include "LCD_DISCO_F469NI.h"

#include "mbed.h"
#include "string"
using std::string;

#define LCD_TOOLS_H

#define LCD_CYCLE_DISPLAY_DURATION 3000ms
#define LCD_CYCLE_DISPLAY_OFF_DURATION 2000ms
#define INTERRUPT_DISPLAY_DURATION 5000ms

static void initLcd(LCD_DISCO_F469NI lcd);
static void exitLcd(LCD_DISCO_F469NI lcd);
static void displayText(string text, LCD_DISCO_F469NI lcd, uint16_t lineHeightPosition);

void displayTextFromInterrupt(string text, LCD_DISCO_F469NI lcd);
void cycleLcdWithText(tuple <LCD_DISCO_F469NI, string>* data);

void setLcdRunState(bool canLcdRun);
bool getLcdRunState();

#endif