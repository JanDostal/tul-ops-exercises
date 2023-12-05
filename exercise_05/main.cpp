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
        initTouchDisplay();
        activateBomb();
        
        bombDetonateEvent.start(detonateBomb);
        bombDeactivateEvent.start(deactivateBomb);
        bombCountdownResetEvent.start(resetBombCountdown);

        touchDisplayTimerUpdater.start(initTouchDisplayTimer);
        touchDisplayTouchEventer.start(checkForTouchEvent);

        while (true)
        {
        }

        exitTouchDisplay();
    }
}
