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
            { .color = LCD_COLOR_RED, .parkingTimeMilliseconds = 4000, .notParkingTimeMilliseconds = 24000 };
        carThread1.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference =
            { .color = LCD_COLOR_BLUE, .parkingTimeMilliseconds = 8000, .notParkingTimeMilliseconds = 20000 };
        carThread2.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
            { .color = LCD_COLOR_GREEN, .parkingTimeMilliseconds = 12000, .notParkingTimeMilliseconds = 16000 };
        carThread3.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
            { .color = LCD_COLOR_YELLOW, .parkingTimeMilliseconds = 16000, .notParkingTimeMilliseconds = 12000 };
        carThread4.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
            { .color = LCD_COLOR_ORANGE, .parkingTimeMilliseconds = 20000, .notParkingTimeMilliseconds = 8000 };
        carThread5.start(callback(driveCar, carReference));

        carReference = (CAR_OBJECT) malloc(sizeof(CAR));
        *carReference = 
            { .color = LCD_COLOR_BROWN, .parkingTimeMilliseconds = 24000, .notParkingTimeMilliseconds = 4000 };
        carThread6.start(callback(driveCar, carReference));

        while (true)
        {
        }

        exitCarPark();
    } 
}
