#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "drawer.h"

void sutherlandHodgman(Drawer *drawer, polygon_t clip, polygon_t figure, QColor visible_color);

int check_convex(polygon_t &polygon);
bool check_cross(polygon_t &polygon);

#endif // ALGORITHM_H
