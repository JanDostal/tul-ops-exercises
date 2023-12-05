#include "touchLcdTools.h"

#include "explosionTools.h"

#include "LCD_DISCO_F469NI.h"
#include "TS_DISCO_F469NI.h"

#include "mbed.h"
#include "string"

LCD_DISCO_F469NI lcd;
TS_DISCO_F469NI ts;

const uint32_t touchScreenWidth = lcd.GetXSize();
const uint32_t touchScreenHeight = lcd.GetYSize();
const uint32_t touchScreenButtonWidth = touchScreenWidth / TOUCH_LCD_DISPLAY_BUTTONS_COUNT;
uint32_t touchScreenButtonHeight;

Ticker touchDisplayTimer;
volatile double timerCurrentStateMilliseconds;

Mutex touchDisplayUpdate_mutex;

void initTouchDisplay() 
{
    ts.Init(touchScreenWidth, touchScreenHeight);

    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font24);
    
    initTouchDisplayButtons();
}

void exitTouchDisplay() 
{
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font24);
}

static void initTouchDisplayButtons() 
{
    touchScreenButtonHeight = touchScreenHeight - LINE(TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION);

    uint32_t buttonYPosition;
    uint32_t buttonXPosition;
    uint32_t touchScreenButtonsColors[TOUCH_LCD_DISPLAY_BUTTONS_COUNT] = TOUCH_LCD_DISPLAY_BUTTONS_COLORS;

    for (int index = 0; index < TOUCH_LCD_DISPLAY_BUTTONS_COUNT; index++) 
    {
        buttonYPosition = touchScreenHeight - touchScreenButtonHeight;
        buttonXPosition = index * touchScreenButtonWidth;

        lcd.SetTextColor(touchScreenButtonsColors[index]);
        lcd.FillRect(buttonXPosition, buttonYPosition, touchScreenButtonWidth, touchScreenButtonHeight);
    }
}

void initTouchDisplayTimer() 
{
    timerCurrentStateMilliseconds = EXPLOSION_COUNTDOWN_MILLISECONDS;

    std::chrono::microseconds timerUpdateFrequency(TOUCH_LCD_DISPLAY_TIMER_REFRESH_FREQUENCY_MILLISECONDS * 1000);
    touchDisplayTimer.attach(&updateTouchDisplayTimerState, timerUpdateFrequency);

    char timerStateTextInfoBuffer[50];
    std::string timerStateTextInfo;

    while (true)
    {
        touchDisplayUpdate_mutex.lock();

        std::strcpy(timerStateTextInfoBuffer, "");
        std::sprintf(timerStateTextInfoBuffer, "Time to explosion: %.1f seconds", 
            timerCurrentStateMilliseconds / 1000);
        timerStateTextInfo = timerStateTextInfoBuffer;

        lcd.ClearStringLine(TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION);
        lcd.SetTextColor(LCD_COLOR_WHITE);
        lcd.DisplayStringAt(0, LINE(TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION), 
            (uint8_t*) timerStateTextInfo.c_str(), CENTER_MODE);

        ThisThread::sleep_for(TOUCH_LCD_DISPLAY_TIMER_REFRESH_FREQUENCY_MILLISECONDS);

        touchDisplayUpdate_mutex.unlock();
    }
}

static void updateTouchDisplayTimerState() 
{
    timerCurrentStateMilliseconds = 
        timerCurrentStateMilliseconds - TOUCH_LCD_DISPLAY_TIMER_REFRESH_FREQUENCY_MILLISECONDS;
}

static int* generateExplosionEventsFlagsRandomizedIndeces() 
{
    const size_t eventsFlagsCount = getExplosionEventsFlagsCount();
    int* explosionEventsFlagsRandomizedIndeces = new int[eventsFlagsCount];

    bool isEventFlagIndexDuplicate;
    int randomGeneratedExplosionEventFlagIndex;

    for (int eventsFlagsRandomizedIndecesIndex = 0; 
        eventsFlagsRandomizedIndecesIndex < eventsFlagsCount; 
        eventsFlagsRandomizedIndecesIndex++) 
    {
        isEventFlagIndexDuplicate = false;

        do
        {
            randomGeneratedExplosionEventFlagIndex = std::rand() % eventsFlagsCount;

            for (int checkedEventsFlagsRandomizedIndecesIndex = 0;
                 checkedEventsFlagsRandomizedIndecesIndex < eventsFlagsRandomizedIndecesIndex && 
                 isEventFlagIndexDuplicate == false;
                 checkedEventsFlagsRandomizedIndecesIndex++) 
            {
                if (explosionEventsFlagsRandomizedIndeces[checkedEventsFlagsRandomizedIndecesIndex] == 
                    randomGeneratedExplosionEventFlagIndex) isEventFlagIndexDuplicate = true;
            }
        }
        while (isEventFlagIndexDuplicate == true);

        explosionEventsFlagsRandomizedIndeces[eventsFlagsRandomizedIndecesIndex] = 
            randomGeneratedExplosionEventFlagIndex;
    }

    return explosionEventsFlagsRandomizedIndeces;
}

static int* generateTouchDisplayButtonsBoundaries() 
{
    const size_t displayButtonsBoundariesCount = TOUCH_LCD_DISPLAY_BUTTONS_COUNT + 1;
    int* touchDisplayButtonsBoundaries = new int[displayButtonsBoundariesCount];

    for (int displayButtonsBoundaryIndex = 0; displayButtonsBoundaryIndex < displayButtonsBoundariesCount; 
        displayButtonsBoundaryIndex++) 
    {
        touchDisplayButtonsBoundaries[displayButtonsBoundaryIndex] = 
            displayButtonsBoundaryIndex * touchScreenButtonWidth;
    }

    return touchDisplayButtonsBoundaries;
}

void checkForTouchEvent() 
{
    int* explosionEventsFlagsRandomizedIndeces = generateExplosionEventsFlagsRandomizedIndeces();
    int* touchDisplayButtonsBoundaries = generateTouchDisplayButtonsBoundaries();

    const uint32_t touchDisplayTimerYPosition = touchScreenHeight - touchScreenButtonHeight;
    bool wasTouchDetected;

    TS_StateTypeDef displayTouchState;
    Mutex& bombEventHandler_mutex = getBombEventHandlerMutex(); 

    while (true) 
    {
        bombEventHandler_mutex.lock();

        if (getWasBombDisarmedStatus() == false) 
        {
            ts.GetState(&displayTouchState);

            wasTouchDetected = false;

            for (int touchDisplayButtonIndex = 0; 
                touchDisplayButtonIndex < TOUCH_LCD_DISPLAY_BUTTONS_COUNT && wasTouchDetected == false; 
                touchDisplayButtonIndex++)
            {
                if (displayTouchState.touchDetected > 0 &&
                (displayTouchState.touchY[0] > touchDisplayTimerYPosition && 
                displayTouchState.touchY[0] < touchScreenHeight) &&
                (displayTouchState.touchX[0] > touchDisplayButtonsBoundaries[touchDisplayButtonIndex] && 
                displayTouchState.touchX[0] < touchDisplayButtonsBoundaries[touchDisplayButtonIndex + 1])) 
                {
                    setExplosionEventFlag(explosionEventsFlagsRandomizedIndeces[touchDisplayButtonIndex]);
                    wasTouchDetected = true;
                }
            }
        }

        bombEventHandler_mutex.unlock();
    }

    delete(explosionEventsFlagsRandomizedIndeces);
    delete(touchDisplayButtonsBoundaries);
}

void activateTouchDisplayGetJinxedMode() 
{
    touchDisplayUpdate_mutex.lock();

    std::string deathText = "Get Jinxed :) :) :) :) :)";

    lcd.Clear(LCD_COLOR_RED);
    lcd.SetBackColor(LCD_COLOR_RED);
    lcd.SetTextColor(LCD_COLOR_WHITE);

    lcd.DisplayStringAt(0, LINE(TOUCH_LCD_DISPLAY_TIMER_LINE_POSITION), 
        (uint8_t*) deathText.c_str(), CENTER_MODE);

    ThisThread::sleep_for(EXPLOSION_GET_JINXED_MODE_DURATION_MILLISECONDS);

    touchDisplayUpdate_mutex.unlock();
}

void resetTouchDisplayTimer() 
{
    timerCurrentStateMilliseconds = EXPLOSION_COUNTDOWN_MILLISECONDS;
}

void stopTouchDisplayTimer() 
{
    touchDisplayTimer.detach();
}