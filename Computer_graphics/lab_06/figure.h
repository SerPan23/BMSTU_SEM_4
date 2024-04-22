#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>

class Figure
{
public:
    Figure();
    Figure(const Figure &figure);

    void add_point(const Point& point);
    void close();
    void clear();
    bool is_closed();


    Point& get_point(int n);
    int size();

private:
    std::vector<Point> data;
    bool closed;
};

using figures_t = std::vector<Figure>;


#endif // FIGURE_H
