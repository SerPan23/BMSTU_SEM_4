#include "algorithm.h"

#include <cmath>

int vector_product(const Point &v1, const Point &v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

int scalar_mul(const Point &v1, const Point &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}


Point get_vector(line_t l)
{
    return Point(l.end.x() - l.start.x(), l.end.y() - l.start.y());
}

Point get_vector(Point &d1, Point &d2)
{
    return get_vector(line_t{d1, d2});
}

Point get_normal(Point &d1, Point &d2, Point &d3)
{
    Point vec = get_vector(d1, d2);
    Point normal;

    if (vec.y())
        normal = Point(1, - vec.x() / vec.y());
    else
        normal = Point(0, 1);

    if (scalar_mul(get_vector(d2, d3), normal) < 0)
        normal = Point(-normal.x(), -normal.y());

    return normal;
}

bool check_cross(polygon_t &polygon)
{
    for (size_t i = 0; i < polygon.lines.size() - 1; i++)
    {
        Point p1 = polygon.lines[i].start;
        Point p2 = polygon.lines[i].end;
        for (size_t j = i + 1; j < polygon.lines.size(); j++) {
            Point p3 = polygon.lines[j].start;
            Point p4 = polygon.lines[j].end;
            int v1 = vector_product(p3 - p4, p3 - p1);
            int v2 = vector_product(p3 - p4, p3 - p2);
            int v3 = vector_product(p1 - p2, p1 - p3);
            int v4 = vector_product(p1 - p2, p1 - p4);
            if (v1 > 0 && v2 < 0)
                return true;
            if (v1 < 0 && v2 > 0)
                return true;
            if (v3 > 0 && v4 < 0)
                return true;
            if (v3 < 0 && v4 > 0)
                return true;
        }
    }
    return false;
}

int sign(int num)
{
    if (num == 0)
        return 0;
    return (num >= 0) ? 1 : -1;
}


int check_convex(polygon_t &polygon)
{
    size_t size = polygon.points.size();
    if (size < 3)
        return false;

    Point v1 = get_vector(polygon.lines[polygon.lines.size() - 1]);
    Point v2 = get_vector(polygon.lines[0]);

    int prev = sign(vector_product(v1, v2));

    for (size_t i = 0; i < polygon.lines.size() - 1; i++)
    {
        v1 = get_vector(polygon.lines[i]);
        v2 = get_vector(polygon.lines[i + 1]);

        int cur = sign(vector_product(v1, v2));
        // если случай с двумя отрезками на одной прямой валиден
        if (cur == 0 || prev == 0)
            continue;
        //
        if (prev != cur)
            return 0;
        prev = cur;
    }

    return prev;
}
