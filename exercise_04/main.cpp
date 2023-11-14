#include "lcdTools.h"

#include "mbed.h"

LCD_DISCO_F469NI lcd;

Thread carOneThread;
Thread carTwoThread;
Thread carThreeThread;
Thread carFourThread;
Thread carFiveThread;
Thread carSixThread;

int main()
{
    bool canRun = true;
    
    if (canRun == true) 
    {
        lcdThread.start(callback(cycleLcdWithText, &lcdThreadData));
        ledThread.start(callback(blinkLed, &led));

        button.rise(&handleButtonPressed);

        while (true) 
        {
            if (getLcdRunState() == false) 
            {
                displayTextFromInterrupt(buttonText, lcd);
                setLcdRunState(true);
            }
        }
    }
}
