#ifndef CAR_H

#include "mbed.h"

#define CAR_H

typedef uint32_t color;

typedef struct
{
    color color;
	uint32_t carParkOccupationDurationMilliseconds;
    uint32_t outOfCarParkDurationMilliseconds;
} CAR, * CAR_OBJECT;

#endif