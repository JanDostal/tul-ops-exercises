#ifndef CAR_H

#include "mbed.h"

#define CAR_H

typedef uint32_t color;
typedef std::chrono::microseconds timems;

typedef struct
{
	color color;
	timems parkingTimeMilliseconds;
    timems notParkingTimeMilliseconds;
}
CAR_ITEM, * CAR_ITEM_OBJECT;

#endif