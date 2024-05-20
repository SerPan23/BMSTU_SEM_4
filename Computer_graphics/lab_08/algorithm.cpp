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

bool check_cross(clip_t &cut)
{
    for (size_t i = 0; i < cut.lines.size() - 1; i++)
    {
        Point p1 = cut.lines[i].start;
        Point p2 = cut.lines[i].end;
        for (size_t j = i + 1; j < cut.lines.size(); j++) {
            Point p3 = cut.lines[j].start;
            Point p4 = cut.lines[j].end;
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


int check_convex(clip_t &cut)
{
    size_t size = cut.points.size();
    if (size < 3)
        return false;

    Point v1 = get_vector(cut.lines[cut.lines.size() - 1]);
    Point v2 = get_vector(cut.lines[0]);

    int prev = sign(vector_product(v1, v2));

    for (size_t i = 0; i < cut.lines.size() - 1; i++)
    {
        v1 = get_vector(cut.lines[i]);
        v2 = get_vector(cut.lines[i + 1]);

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
bool cut_line(line_t& res_line, line_t src, clip_t& clip)
{
    int conv = check_convex(clip);

    Point D(src.end.x() - src.start.x(), src.end.y() - src.start.y());
    double lt = 0, ht = 1;

    for (int i = 0; i < clip.lines.size(); i++)
    {
        Point f = clip.lines[i].start;
        Point p2 = clip.lines[i].end;
        Point n_in(-conv * (p2.y() - f.y()), conv * (p2.x() - f.x()));
        Point W = src.start - f;
        double Wsc = scalar_mul(W, n_in);
        double Dsc = scalar_mul(D, n_in);

        if (Dsc)
        {
            double t = -Wsc / Dsc;
            if (Dsc > 0)
            {
                if (t > 1)
                    return false;
                else if (t > lt)
                    lt = t;
            } else
            {
                if  (t < 0)
                    return false;
                else if (t < ht)
                    ht = t;
            }
        }
        else if (Wsc < 0)
            return false;
    }

    if (lt > ht)
        return false;

    Point tmp(src.end.x() - src.start.x(), src.end.y() - src.start.y());
    Point l_tmp(int(tmp.x() * lt), int(tmp.y() * lt));
    res_line.start = Point(src.start.x() + l_tmp.x(), src.start.y() + l_tmp.y());
    Point h_tmp(int(tmp.x() * ht), int(tmp.y() * ht));
    res_line.end = Point(src.start.x() + h_tmp.x(), src.start.y() + h_tmp.y());

    return true;
}

// #include <iostream>
void cyrus_beck_cut(Drawer *drawer, clip_t clip, lines_t lines, QColor visible_color)
{
    for (int i = 0; i < lines.size(); i++)
    {
        line_t visible_line;
        if (cut_line(visible_line, lines[i], clip))
        {
            // std::cout << "Line: (" << lines[i].start.x() << ";" << lines[i].start.y() << ") ("
            //     << lines[i].end.x() << ";" << lines[i].end.y() << ")\n";
            // std::cout << "Vis_Line: (" << visible_line.start.x() << ";" << visible_line.start.y() << ") ("
            //           << visible_line.end.x() << ";" << visible_line.end.y() << ")\n";

            drawer->draw_line(visible_line.start, visible_line.end, visible_color);
        }
    }
}
