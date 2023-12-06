#include "mbed.h"

#include "explosionTools.h"
#include "touchLcdTools.h"

Thread touchDisplayTouchEventer;
Thread touchDisplayTimerUpdater;

Thread bombDetonateEvent;
Thread bombDeactivateEvent;
Thread bombCountdownResetEvent;

int main()
{
    bool canRun = true;
    
    if (canRun == true) 
    {
        TOUCH_DISPLAY_BUTTONS_DATA_REFERENCE buttonsDataReference = initTouchDisplay();
        activateBomb();
        
        bombDetonateEvent.start(detonateBomb);
        bombDeactivateEvent.start(deactivateBomb);
        bombCountdownResetEvent.start(resetBombCountdown);

        touchDisplayTimerUpdater.start(initTouchDisplayTimer);
        touchDisplayTouchEventer.start(callback(checkForTouchEvent, buttonsDataReference));

        while (true)
        {
        }

        exitTouchDisplay();
    }
}
