#ifndef EXPLOSION_TOOLS_H

#include "mbed.h"

#define EXPLOSION_TOOLS_H

#define EXPLOSION_COUNTDOWN_MILLISECONDS 60000
#define EXPLOSION_EVENTS_FLAGS { 0x4, 0x2, 0x1 }
#define EXPLOSION_GET_JINXED_MODE_DURATION_MILLISECONDS 3000

void activateBomb();

void deactivateBomb();
void detonateBomb();
void resetBombCountdown();

size_t getExplosionEventsFlagsCount();
bool getWasBombDisarmedStatus();
Mutex& getBombEventHandlerMutex();
void setExplosionEventFlag(int index);

#endif