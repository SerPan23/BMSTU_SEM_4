#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "point.h"
#include <vector>

struct line
{
    Point start;
    Point end;
};

using line_t = struct line;

using lines_t = std::vector<line_t>;

struct rect
{
    Point left_top;
    Point right_down;
};

using rect_t = struct rect;



#endif // ALGORITHM_H
