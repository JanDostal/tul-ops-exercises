#include "lcdTools.h"

volatile bool canRun = true;

static void initLcd(LCD_DISCO_F469NI lcd) 
{
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font20);
}

static void exitLcd(LCD_DISCO_F469NI lcd) 
{
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font20);
}

static void displayText(string text, LCD_DISCO_F469NI lcd, uint16_t lineHeightPosition) 
{
    lcd.DisplayStringAt(0, LINE(lineHeightPosition), (uint8_t*) text.c_str(), CENTER_MODE);
}

void displayTextFromInterrupt(string text, LCD_DISCO_F469NI lcd)
{
    initLcd(lcd);

    displayText(text, lcd, 1);
    ThisThread::sleep_for(INTERRUPT_DISPLAY_DURATION);

    exitLcd(lcd);
}

void cycleLcdWithText(tuple <LCD_DISCO_F469NI, string>* data) 
{
    initLcd(get<0>(*data));

    while (true) 
    {
        if (canRun == true) displayText(get<1>(*data), get<0>(*data), 1);
        else continue;

        if (canRun == true) ThisThread::sleep_for(LCD_CYCLE_DISPLAY_DURATION);
        else continue;

        if (canRun == true) exitLcd(get<0>(*data));
        else continue;

        if (canRun == true) ThisThread::sleep_for(LCD_CYCLE_DISPLAY_OFF_DURATION);
        else continue;
    }

    exitLcd(get<0>(*data));
}

void setLcdRunState(bool canLcdRun) 
{
    canRun = canLcdRun;
}

bool getLcdRunState()
{
    return canRun;
}