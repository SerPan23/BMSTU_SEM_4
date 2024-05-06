#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "point.h"
#include <vector>
#include "drawer.h"

typedef bool point_code_t[4];

void simple_cut(Drawer *drawer, rect_t clipper, lines_t line, QColor visible_color);



#endif // ALGORITHM_H
