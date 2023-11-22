#include "carPark.h"

#include "LCD_DISCO_F469NI.h"
#include "mbed.h"
#include "vector"

LCD_DISCO_F469NI lcd;
const uint32_t carParkWidth = lcd.GetXSize();
const uint32_t carParkHeight = lcd.GetYSize();
const uint32_t carParkPlaceWidth = carParkWidth / CAR_PARK_CAPACITY;
const uint32_t carParkPlaceHeight = carParkHeight;

vector<CAR_OBJECT> carPark;

Mutex carParkUpdate_mutex;
Semaphore carParkArea(CAR_PARK_CAPACITY, CAR_PARK_CAPACITY);

void initCarPark() 
{
    lcd.Clear(LCD_COLOR_GRAY);
    lcd.SetBackColor(LCD_COLOR_GRAY);
    lcd.SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_SetFont(&Font20);

    for (int parkingPlacePosition = 1; parkingPlacePosition <= CAR_PARK_CAPACITY; parkingPlacePosition++) 
    {
        carPark.push_back(NULL);
    }
}

void exitCarPark() 
{
    lcd.Clear(LCD_COLOR_GRAY);
    lcd.SetBackColor(LCD_COLOR_GRAY);
    lcd.SetTextColor(LCD_COLOR_GRAY);
    BSP_LCD_SetFont(&Font20);
}

void driveCar(CAR_OBJECT carReference) 
{
    while (true)
    {
        carParkArea.acquire();
        
        carParkUpdate_mutex.lock();
        parkCar(carReference);
        carParkUpdate_mutex.unlock();

        ThisThread::sleep_for(carReference->parkingTimeMilliseconds);

        carParkUpdate_mutex.lock();
        unparkCar(carReference);
        carParkUpdate_mutex.unlock();

        carParkArea.release();

        ThisThread::sleep_for(carReference->notParkingTimeMilliseconds);
    }
}

static void parkCar(CAR_OBJECT carReference) 
{
    int index = 0;
    while(carPark.at(index) != NULL) index++;
    carPark.at(index) = carReference;

    uint32_t carYPosition = 0;
    uint32_t carXPosition = index * carParkPlaceWidth;

    lcd.SetTextColor(carReference->color);
    lcd.FillRect(carXPosition, carYPosition, carParkPlaceWidth, carParkPlaceHeight);
}

static void unparkCar(CAR_OBJECT carReference) 
{
    int index = 0;
    while(carPark.at(index) != carReference) index++;
    carPark.at(index) = NULL;

    uint32_t carYPosition = 0;
    uint32_t carXPosition = index * carParkPlaceWidth;

    lcd.SetTextColor(LCD_COLOR_GRAY);
    lcd.FillRect(carXPosition, carYPosition, carParkPlaceWidth, carParkPlaceHeight);
}