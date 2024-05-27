#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QTimer>

enum Direction {
    DOWN = -1,
    STAY = 0,
    UP = 1
};

#define FLOORS_COUNT 12

#define ONE_FLOOR_PASS_TIME 1000
#define DOORS_DEFAULT_DELAY 2000
#define PASSENGERS_WAITING_DELAY 2000

#define START_FLOOR 1
#define NO_TARGET (-1)

#endif // CONSTANTS_H
