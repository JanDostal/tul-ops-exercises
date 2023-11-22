#ifndef CAR_PARK_H

#include "car.h"

#define CAR_PARK_H

#define CAR_PARK_CAPACITY 4

void initCarPark();
void exitCarPark();
void driveCar(CAR_OBJECT carReference);

static void parkCar(CAR_OBJECT carReference);
static void unparkCar(CAR_OBJECT carReference);

#endif