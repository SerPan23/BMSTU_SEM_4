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

Point Point::operator+(const Point &point) const
{
    return Point(this->_x + point._x, this->_y + point._y);
}
Point Point::operator+(Point &point)
{
    return Point(this->_x + point._x, this->_y + point._y);
}

Point Point::operator-(const Point &point) const
{
    return Point(this->_x - point._x, this->_y - point._y);
}
Point Point::operator-(Point &point)
{
    return Point(this->_x - point._x, this->_y - point._y);
}

int Point::x() const
{
    return this->_x;
}

int Point::y() const
{
    return this->_y;
}


void Point::setX(int x)
{
    _x = x;
}
void Point::setY(int y)
{
    _y = y;
}
