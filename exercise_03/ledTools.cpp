#include "ledTools.h"

static void initLed(DigitalOut led) 
{
    led = false;
}

static void exitLed(DigitalOut led) 
{
    led = false;
}

void blinkLed(DigitalOut* led) 
{
    initLed(*led);

    while (true) 
    {
        *led = true;
        ThisThread::sleep_for(LIGHTING_ON_RATE);
        *led = false;
        ThisThread::sleep_for(LIGHTING_OFF_RATE);
    }

    exitLed(*led);
}