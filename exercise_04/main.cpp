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

        CAR cars[] =
        {
            { .color = LCD_COLOR_RED, .parkingTimeMilliseconds = 800, .notParkingTimeMilliseconds = 5000 },
            { .color = LCD_COLOR_BLUE, .parkingTimeMilliseconds = 400, .notParkingTimeMilliseconds = 600 },
            { .color = LCD_COLOR_GREEN, .parkingTimeMilliseconds = 5000, .notParkingTimeMilliseconds = 400 },
            { .color = LCD_COLOR_YELLOW, .parkingTimeMilliseconds =600, .notParkingTimeMilliseconds = 3000 },
            { .color = LCD_COLOR_ORANGE, .parkingTimeMilliseconds = 1000, .notParkingTimeMilliseconds = 800 },
            { .color = LCD_COLOR_BROWN, .parkingTimeMilliseconds = 3000, .notParkingTimeMilliseconds = 1000 }
        };

        int carsArrayLength = sizeof(cars) / sizeof(CAR);

        CAR_OBJECT carReference;
        for (int i = 0; i < carsArrayLength; i++) 
        {
            Thread carThread;

            carReference = (CAR_OBJECT) malloc(sizeof(CAR));
            *carReference = cars[i];

            carThread.start(callback(driveCar, carReference));
        }

        while (true)
        {
        }

        exitCarPark();
    } 
}
