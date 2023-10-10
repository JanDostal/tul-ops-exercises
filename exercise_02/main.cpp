/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "morse.h"


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
    init(led);

    string str = "honza";

    if (str.empty()) 
    {
        run = false;
    }

    while (run) 
    {
        morse(str, led);
    }
}
