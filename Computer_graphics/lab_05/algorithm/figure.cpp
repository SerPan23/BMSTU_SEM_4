#include "figure.h"

Figure::Figure()
{
    this->is_closed = false;
}

Figure::Figure(Figure const &figure)
{
    this->is_closed = figure.is_closed;

    this->data = figure.data;
}

void Figure::add_point(const Point& point)
{
    this->data.push_back(point);
}

void Figure::closed()
{
    this->is_closed = true;
}

void Figure::clear()
{
    this->is_closed = false;
    this->data.clear();
}

Point& Figure::get_point(int n)
{
    return this->data[n];
}

int Figure::size()
{
    return this->data.size();
}
