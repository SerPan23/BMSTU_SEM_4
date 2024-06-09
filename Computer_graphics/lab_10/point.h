#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(int x, int y);
    Point(const Point &point);

    Point &operator=(const Point &point);
    Point &operator=(const Point &&point);

    Point operator+(const Point &point) const;
    Point operator+(Point &point);

    Point operator-(const Point &point) const;
    Point operator-(Point &point);

    bool is_null() { return !(_x > 0 && _y > 0); };
    bool is_null() const { return !(_x > 0 && _y > 0); };

    bool operator==(Point& p) { return _x == p._x && _y == p._y; };
    bool operator!=(Point& p) { return !operator==(p); };


    int x() const;
    int y() const;

    void setX(int x);
    void setY(int y);

private:
    int _x;
    int _y;
};

#endif // POINT_H
