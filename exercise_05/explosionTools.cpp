#include "explosionTools.h"

#include "touchLcdTools.h"

#include "mbed.h"

const uint32_t explosionEventsFlags[TOUCH_LCD_DISPLAY_BUTTONS_COUNT] = EXPLOSION_EVENTS_FLAGS;
const size_t explosionEventsFlagsCount = sizeof(explosionEventsFlags) / sizeof(uint32_t);

EventFlags explosionEvents;

Mutex bombEventHandler_mutex;

void activateBomb()
{
    Watchdog& explosionCountdown = Watchdog::get_instance();

    // watchdog countdown not accurate, it will be about 3 seconds more
    explosionCountdown.start(EXPLOSION_COUNTDOWN_MILLISECONDS);
}

void deactivateBomb() 
{
    explosionEvents.wait_any(explosionEventsFlags[0]);

    bombEventHandler_mutex.lock();

    Watchdog& explosionCountdown = Watchdog::get_instance();
    stopTouchDisplayTimer();

    while (true)
    {
        explosionCountdown.kick();
    }

    bombEventHandler_mutex.unlock();
}

void detonateBomb() 
{
    explosionEvents.wait_any(explosionEventsFlags[1]);

    bombEventHandler_mutex.lock();

    Watchdog& explosionCountdown = Watchdog::get_instance();
    explosionCountdown.start(EXPLOSION_GET_JINXED_MODE_DURATION_MILLISECONDS);
    
    activateTouchDisplayGetJinxedMode();

    bombEventHandler_mutex.unlock();
}

void resetBombCountdown() 
{
    Watchdog& explosionCountdown = Watchdog::get_instance();

    while (true) 
    {
        explosionEvents.wait_any(explosionEventsFlags[2]);

        bombEventHandler_mutex.lock();

        explosionCountdown.kick();
        resetTouchDisplayTimer();

        bombEventHandler_mutex.unlock();
    }
}

size_t getExplosionEventsFlagsCount() 
{
    return explosionEventsFlagsCount;
}

Mutex& getBombEventHandlerMutex() 
{
    return bombEventHandler_mutex;
}

void setExplosionEventFlag(int index) 
{
    explosionEvents.set(explosionEventsFlags[index]);
}