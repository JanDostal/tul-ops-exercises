#include "mbed.h"

#include "carPark.h"
#include "car.h"
#include "LCD_DISCO_F469NI.h"

int main()
{
    bool canRun = true;
    
    if (canRun == true) 
    {
        initCarPark();

        Thread carThread1;
        Thread carThread2;
        Thread carThread3;
        Thread carThread4;
        Thread carThread5;
        Thread carThread6;

        CAR_OBJECT carReference;

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
        { 
            .color = LCD_COLOR_RED, 
            .carParkOccupationDurationMilliseconds = 4000, 
            .outOfCarParkDurationMilliseconds = 24000 
        };
        carThread1.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference =
        { 
            .color = LCD_COLOR_BLUE, 
            .carParkOccupationDurationMilliseconds = 8000, 
            .outOfCarParkDurationMilliseconds = 20000 
        };
        carThread2.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
        { 
            .color = LCD_COLOR_GREEN, 
            .carParkOccupationDurationMilliseconds = 12000, 
            .outOfCarParkDurationMilliseconds = 16000 
        };
        carThread3.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
        { 
            .color = LCD_COLOR_YELLOW, 
            .carParkOccupationDurationMilliseconds = 16000, 
            .outOfCarParkDurationMilliseconds = 12000 
        };
        carThread4.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
        {   
            .color = LCD_COLOR_ORANGE, 
            .carParkOccupationDurationMilliseconds = 20000, 
            .outOfCarParkDurationMilliseconds = 8000 
        };
        carThread5.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
        { 
            .color = LCD_COLOR_BROWN, 
            .carParkOccupationDurationMilliseconds = 24000, 
            .outOfCarParkDurationMilliseconds = 4000 
        };
        carThread6.start(callback(driveCar, carReference));

        while (true)
        {
        }

        exitCarPark();
    } 
}
