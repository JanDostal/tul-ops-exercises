#ifndef LED_TOOLS_H

#include "mbed.h"

#define LED_TOOLS_H

#define LIGHTING_ON_RATE 1000ms
#define LIGHTING_OFF_RATE 2000ms

static void initLed(DigitalOut led);
static void exitLed(DigitalOut led);

void blinkLed(DigitalOut* led);

#endif