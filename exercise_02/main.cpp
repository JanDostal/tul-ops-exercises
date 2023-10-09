/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>
#include <string>

#include "morse.h"

void blink(DigitalOut led, uint32_t delay) 
{
    led = true;
    ThisThread::sleep_for(delay);
    led = false;
}

void morse(string str, DigitalOut led) 
{
    for(char& c : str) 
    {
        if (c == 'h') 
        {
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_END);
        }
        if (c == 'o') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_END);
        }
        if (c == 'n') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_END);
        }
        if (c == 'z') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_END);
        }
        if (c == 'a') 
        {
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_END);
        }
    }
    
    ThisThread::sleep_for(2000);
}

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
    bool run = true;

    DigitalOut led(LED1);


    string str = "honza";
    init(led);

    if (str.empty()) 
    {
        run = false;
    }

    while (run) 
    {
        morse(str, led);
    }
}
