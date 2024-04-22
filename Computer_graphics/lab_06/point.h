#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(int x, int y);
    explicit Point(const Point &point);

    Point &operator=(const Point &point);
    Point &operator=(const Point &&point);


    int x() const;
    int y() const;

private:
    int _x;
    int _y;
};

#endif // POINT_H
