/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

#define LIGHTING_ON_RATE 1000ms
#define LIGHTING_OFF_RATE 2000ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
 
 
    while (true) {
        led = !led;
        
        if (led == 1) ThisThread::sleep_for(LIGHTING_ON_RATE);
        else ThisThread::sleep_for(LIGHTING_OFF_RATE);
    }
}
