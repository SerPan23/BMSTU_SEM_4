#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "drawer.h"

void cyrus_beck_cut(Drawer *drawer, clip_t clip, lines_t lines, QColor visible_color);

int check_convex(clip_t &cut);
bool check_cross(clip_t &cut);

#endif // ALGORITHM_H
