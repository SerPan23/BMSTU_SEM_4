#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>

class Figure
{
public:
    Figure();
    Figure(Figure const &figure);

    void add_point(const Point& point);
    void closed();
    void clear();

    Point& get_point(int n);
    int size();

private:
    std::vector<Point> data;
    bool is_closed;
};

#endif // FIGURE_H
