#include "algorithm.h"

#include <iostream>

int find_point_code(point_code_t& code, const Point& p, const rect_t& cut)
{
    int min_x = cut.p1.x() < cut.p2.x() ? cut.p1.x() : cut.p2.x();
    int max_x = cut.p1.x() > cut.p2.x() ? cut.p1.x() : cut.p2.x();
    int min_y = cut.p1.y() < cut.p2.y() ? cut.p1.y() : cut.p2.y();
    int max_y = cut.p1.y() > cut.p2.y() ? cut.p1.y() : cut.p2.y();

    for (size_t i = 0; i < 4; i++)
        code[i] = false;

    if (p.x() < min_x)
        code[0] = true;
    else if (p.x() > max_x)
        code[1] = true;
    if (p.y() < min_y)
        code[2] = true;
    else if (p.y() > max_y)
        code[3] = true;

    int sum = 0;
    for (size_t i = 0; i < 4; i++)
        sum += code[i];
    return sum;
}

bool log_mult(const point_code_t& T1, const point_code_t& T2)
{
    bool mult = 0;
    for (size_t i = 0; i < 4; i++)
        mult += T1[i] && T2[i];
    return mult;
}

Point find_r(const Point& p1, const Point& p2, const Point& q, const rect_t& cut, bool& flag)
{
    int left = cut.p1.x() < cut.p2.x() ? cut.p1.x() : cut.p2.x();
    int right = cut.p1.x() > cut.p2.x() ? cut.p1.x() : cut.p2.x();
    int bottom = cut.p1.y() < cut.p2.y() ? cut.p1.y() : cut.p2.y();
    int top = cut.p1.y() > cut.p2.y() ? cut.p1.y() : cut.p2.y();

    double m = pow(10, 30);
    if (p1.x() != p2.x()) {
        m = static_cast<double>(p2.y() - p1.y()) / (p2.x() - p1.x());
        if (q.x() <= left) {
            int y = static_cast<int>(round(m * (left - q.x()))) + q.y();
            if (y >= bottom && y <= top)
                return { left, y };
        }
        if (q.x() >= right) {
            int y = static_cast<int>(round(m * (right - q.x()))) + q.y();
            if (y >= bottom && y <= top)
                return { right, y };
        }
    }
    if (qFuzzyCompare(m, 0)) {
        flag = false;
        return q;
    }
    if (q.y() >= top) {
        int x = static_cast<int>(round((top - q.y()) / m)) + q.x();
        if (x >= left && x <= right)
            return { x, top };
    }
    if (q.y() <= bottom) {
        int x = static_cast<int>(round((bottom - q.y()) / m)) + q.x();
        if (x >= left && x <= right)
            return { x, bottom };
    }
    flag = false;
    return q;
}

bool cut_line(line_t& res_line, const line_t& src, const rect_t& cut)
{
    bool flag = true;

    point_code_t T1, T2;
    int S1 = find_point_code(T1, src.start, cut);
    int S2 = find_point_code(T2, src.end, cut);

    Point R1 = { 0, 0 }, R2 = { 0, 0 };

    if (S1 == 0 && S2 == 0) {
        R1 = src.start;
        R2 = src.end;
    } else {
        int p = log_mult(T1, T2);
        if (p != 0)
            flag = false;
        else {
            int i = 0;
            Point Q = { 0, 0 };
            if (S1 == 0) {
                R1 = src.start;
                Q = src.end;
                i = 1;
            } else if (S2 == 0) {
                R1 = src.end;
                Q = src.start;
                i = 1;
            }
            while (i < 2) {
                i++;
                if (i == 1) {
                    Q = src.start;
                    R1 = find_r(src.start, src.end, Q, cut, flag);
                    Q = src.end;
                } else
                    R2 = find_r(src.start, src.end, Q, cut, flag);
            }
        }
    }
    if (flag) {
        res_line.start = R1;
        res_line.end = R2;
        return true;
    }

    return flag;
}

void simple_cut(Drawer *drawer, rect_t clipper, lines_t lines, QColor visible_color)
{
    for (int i = 0; i < lines.size(); i++)
    {
        line_t visible_line;
        if (cut_line(visible_line, lines[i], clipper))
        {
            // std::cout << "Line: (" << lines[i].start.x() << ";" << lines[i].start.y() << ") ("
            //     << lines[i].end.x() << ";" << lines[i].end.y() << ")\n";
            // std::cout << "Vis_Line: (" << visible_line.start.x() << ";" << visible_line.start.y() << ") ("
            //           << visible_line.end.x() << ";" << visible_line.end.y() << ")\n";

            drawer->draw_line(visible_line.start, visible_line.end, visible_color);
        }
    }
}
