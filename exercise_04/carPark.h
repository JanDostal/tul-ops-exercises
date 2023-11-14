#ifndef CAR_PARK_H

#include "car.h"

#define CAR_PARK_H

void initCarPark();
void exitCarPark();
void driveCar(CAR_ITEM_OBJECT car);

static void parkCar(CAR_ITEM_OBJECT car);
static void unparkCar();

#endif