#include "point.h"

Point::Point()
{
    this->_x = 0;
    this->_y = 0;
}

Point::Point(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

Point::Point(const Point &point)
{
    this->_x = point.x();
    this->_y = point.y();
}

Point &Point::operator=(const Point &point)
{
    this->_x = point.x();
    this->_y = point.y();

    return *this;
}

Point &Point::operator=(const Point &&point)
{
    this->_x = point.x();
    this->_y = point.y();

    return *this;
}

int Point::x() const
{
    return this->_x;
}

int Point::y() const
{
    return this->_y;
}
