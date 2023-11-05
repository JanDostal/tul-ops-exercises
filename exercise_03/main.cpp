#include "ledTools.h"
#include "lcdTools.h"

#include "mbed.h"

DigitalOut led(LED1);
LCD_DISCO_F469NI lcd;
InterruptIn button(PA_0);

Thread lcdThread;
Thread ledThread;

void handleButtonPressed() 
{
    setLcdRunState(false);
}

int main()
{
    bool canRun = true;

    string buttonText = "Pressed";
    string lcdText = "Hello world";

    if (buttonText.empty() || lcdText.empty())
    {
        canRun = false;
    }
    
    if (canRun == true) 
    {
        tuple <LCD_DISCO_F469NI, string> lcdThreadData = make_tuple(lcd, lcdText);
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
