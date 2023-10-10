#include "morse.h"

void blink(DigitalOut led, uint32_t delay) 
{
    led = true;
    ThisThread::sleep_for(delay);
    led = false;
}

void morse(string str, DigitalOut led) 
{
    for(char c : str) 
    {
        if (c == 'h') 
        {
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_LETTER_END);
        }
        if (c == 'o') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_LETTER_END);
        }
        if (c == 'n') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_LETTER_END);
        }
        if (c == 'z') 
        {
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_LETTER_END);
        }
        if (c == 'a') 
        {
            blink(led, MORSE_DOT);
            ThisThread::sleep_for(MORSE_SIGN_PAUSE);
            blink(led, MORSE_DASH);
            ThisThread::sleep_for(MORSE_LETTER_END);
        }
    }
    
    ThisThread::sleep_for(MORSE_WORD_END);
}