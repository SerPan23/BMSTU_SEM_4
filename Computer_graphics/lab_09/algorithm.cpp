#include "algorithm.h"

#include <cmath>

int vector_product(const Point &v1, const Point &v2)
{
    return v1.x() * v2.y() - v1.y() * v2.x();
}

int scalar_product(const Point &v1, const Point &v2)
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

//----------------ALGO----------------

bool is_visivble(const line_t& src, const Point& p, int norm)
{
    Point v1 = src.end - src.start;
    Point v2 = p - src.start;

    int pr = vector_product(v1, v2);

    if (pr * norm >= 0)
        return true;

    return false;
}

bool find_inter(Point& p, line_t src, line_t sec, int norm)
{
    bool vis1 = is_visivble(src, sec.start, norm);
    bool vis2 = is_visivble(src, sec.end, norm);
    bool is_inter = (vis1 || vis2) && (!(vis1 && vis2));

    if (is_inter) {
        Point cut_vec = src.end - src.start;
        Point pol_vec = sec.end - sec.start;

        long nominator = cut_vec.y() * (sec.start.x() - src.start.x())
                         - cut_vec.x() * (sec.start.y() - src.start.y());
        long denomanator = pol_vec.y() * cut_vec.x() - pol_vec.x() * cut_vec.y();

        if (denomanator == 0)
            p = sec.end;
        else
        {
            double t = (double)nominator / denomanator;
            Point tmp = sec.end - sec.start;
            tmp = { int(tmp.x() * t), int(tmp.y() * t) };
            p = sec.start + tmp;
        }
    }

    return is_inter;
}

void sutherlandHodgman(Drawer *drawer, polygon_t clip, polygon_t figure, QColor visible_color)
{
    int normal = check_convex(clip);
    polygon_t visible_figure = figure;
    for (auto cut_line : clip.lines)
    {
        polygon new_pol;
        for (auto vis_line : visible_figure.lines)
        {
            Point inter;

            bool is_inter = find_inter(inter, cut_line, vis_line, normal);
            if (is_inter)
            {
                new_pol.points.push_back(inter);
                if (new_pol.points.size() > 1)
                    new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 2],
                                             new_pol.points[new_pol.points.size() - 1] });
            }

            bool is_vis = is_visivble(cut_line, vis_line.end, normal);
            if (is_vis)
            {
                new_pol.points.push_back(vis_line.end);
                if (new_pol.points.size() > 1)
                    new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 2],
                                             new_pol.points[new_pol.points.size() - 1] });
            }
        }

        if (new_pol.points.size() == 0)
            return;

        new_pol.is_closed = false;
        if (new_pol.points.size() > 2)
        {
            new_pol.is_closed = true;
            new_pol.lines.push_back({ new_pol.points[new_pol.points.size() - 1],
                                     new_pol.points[0] });
        }

        visible_figure = new_pol;
    }

    drawer->draw_polygon(visible_figure, visible_color);
}
