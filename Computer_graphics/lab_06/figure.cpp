#include "figure.h"

Figure::Figure()
{
    this->closed = false;
}

Figure::Figure(const Figure &figure)
{
    this->closed = figure.closed;

    this->data = figure.data;
}

void Figure::add_point(const Point& point)
{
    this->data.push_back(Point(point));
}

void Figure::close()
{
    this->closed = true;
}

void Figure::clear()
{
    this->closed = false;
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

bool Figure::is_closed()
{
    return this->closed;
}
