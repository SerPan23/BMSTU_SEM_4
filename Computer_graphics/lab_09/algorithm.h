#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "drawer.h"

// void cyrus_beck_cut(Drawer *drawer, clip_t clip, lines_t lines, QColor visible_color);

int check_convex(polygon_t &polygon);
bool check_cross(polygon_t &polygon);

#endif // ALGORITHM_H
