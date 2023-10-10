
#ifndef MORSE_H

#define MORSE_H

#include "mbed.h"
#include "cstdint"
#include "string"
using std::string;

#define MORSE_DASH 450 //300
#define MORSE_DOT 150
#define MORSE_SIGN_PAUSE 150 //500 
#define MORSE_LETTER_END 450 //1000
#define MORSE_WORD_END 1050

void blink(DigitalOut led, uint32_t delay);
void morse(string str, DigitalOut led);

#endif