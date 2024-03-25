#include "algorithms.h"

line_t dda(point_t start, point_t end)
{
    std::vector <pixel_t> pixels;

    if (start.x == end.x && start.y == end.y)
        pixels.push_back(pixel_create((int)round(start.x), (int)round(start.y)));
    else
    {
        double x = start.x;
        double y = start.y;

        int len;
        double dx = (end.x - start.x);
        double dy = (end.y - start.y);

        if (abs(dx) > abs(dy))
            len = abs(dx);
        else
            len = abs(dy);

        dx = dx / len;
        dy = dy / len;

        for (int i = 0; i < len + 1; i++)
        {
            pixels.push_back(pixel_create((int)round(x), (int)round(y)));
            x += dx;
            y += dy;
        }
    }

    return line_t{pixels};
}

int dda_step_count(point_t start, point_t end)
{
    if (start.x == end.x && start.y == end.y)
        return 0;

    double x = start.x;
    double y = start.y;

    int len;
    double dx = (end.x - start.x);
    double dy = (end.y - start.y);


    bool flag = false;
    if (abs(dx) > abs(dy))
        len = abs(dx);
    else
    {
        len = abs(dy);
        flag = true;
    }

    dx = dx / len;
    dy = dy / len;

    int x_prev = x;
    int y_prev = y;
    int steps = 0;

    for (int i = 0; i < len + 1; i++)
    {
        if (flag)
        {
            if (round(x_prev) != round(x))
                steps++;
        }
        else if (round(y_prev) != round(y))
            steps++;

        x_prev = x;
        y_prev = y;

        x += dx;
        y += dy;
    }

    return steps;
}
