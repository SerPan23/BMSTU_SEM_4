#include "algorithms.h"

std::vector <pixel_t> dda(point_t start, point_t end)
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

        if (abs(dx) >= abs(dy))
            len = (int)round(abs(dx));
        else
            len = (int)round(abs(dy));

        dx = dx / len;
        dy = dy / len;

        for (int i = 0; i < len; i++)
        {
            pixels.push_back(pixel_create((int)round(x), (int)round(y)));
            x += dx;
            y += dy;
        }
    }

    return pixels;
}
