/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "LCD_DISCO_F469NI.h"

LCD_DISCO_F469NI lcd;

DigitalOut led1(LED1);


void init(DigitalOut led) 
{
    led = false;
}

void exit(DigitalOut led)
{
    led = false;
}

int main()
{
    led1 = 1;
  
    lcd.DisplayStringAt(0, LINE(1), (uint8_t *)"MBED EXAMPLE", CENTER_MODE);
    wait(1);
  
    while(1)
    {
      lcd.Clear(LCD_COLOR_BLUE);
      lcd.SetBackColor(LCD_COLOR_BLUE);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      wait(0.3);
      lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"DISCOVERY", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"STM32F469NI", CENTER_MODE);
      wait(1);

      lcd.Clear(LCD_COLOR_GREEN);
      
      lcd.SetTextColor(LCD_COLOR_BLUE);
      lcd.FillRect(10, 20, 50, 50);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_BROWN);
      lcd.FillCircle(80, 80, 50);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_YELLOW);
      lcd.FillEllipse(150, 150, 50, 100);
      wait(0.1);
      lcd.SetTextColor(LCD_COLOR_RED);
      lcd.FillCircle(200, 200, 40);
      wait(1);

      lcd.SetBackColor(LCD_COLOR_ORANGE);
      lcd.SetTextColor(LCD_COLOR_CYAN);
      BSP_LCD_SetFont(&Font20);
      lcd.DisplayStringAt(0, LINE(7), (uint8_t *)"HAVE FUN !!!", CENTER_MODE);
      wait(1);

      led1 = !led1;
      wait(0.5);
    }
}
