#include "algorithms.h"

std::vector <pixel_t> bresenham_double(point_t start, point_t end)
{
    std::vector<pixel_t> pixels;

    if (start.x == end.x && start.y == end.y)
        pixels.push_back(pixel_create((int)(start.x), (int)(start.y)));
    else
    {
        int x = start.x;
        int y = start.y;

        int dx = (end.x - start.x);
        int dy = (end.y - start.y);

        int sx = sign(dx);
        int sy = sign(dy);

        dx = abs(dx);
        dy = abs(dy);

        bool exchange = false;

        if (dy > dx)
        {
            std::swap(dx, dy);
            exchange = true;
        }

        double m = 1.0 * dy / dx;
        double error = m - 0.5;

        for (int i = 0; i < dx; i++)
        {
            pixels.push_back(pixel_create(x, y));

            if (error >= 0)
            {
                if (exchange)
                    x += sx;
                else
                    y += sy;

                error -= 1;
            }

            if (error <= 0)
            {
                if (exchange)
                    y += sy;
                else
                    x += sx;

                error += m;
            }
        }
    }

    return pixels;
}

std::vector <pixel_t> bresenham_integer(point_t start, point_t end)
{
    std::vector<pixel_t> pixels;

    if (start.x == end.x && start.y == end.y)
        pixels.push_back(pixel_create((int)round(start.x), (int)round(start.y)));
    else
    {
        int x = start.x;
        int y = start.y;

        int dx = (end.x - start.x);
        int dy = (end.y - start.y);

        int sx = sign(dx);
        int sy = sign(dy);

        dx = abs(dx);
        dy = abs(dy);

        bool exchange = false;

        if (dy > dx)
        {
            std::swap(dx, dy);
            exchange = true;
        }

        double error = 2 * dy - dx;

        for (int i = 0; i < dx; i++)
        {
            pixels.push_back(pixel_create(x, y));

            if (error >= 0)
            {
                if (exchange)
                    x += sx;
                else
                    y += sy;

                error -= 2 * dx;
            }

            if (error <= 0)
            {
                if (exchange)
                    y += sy;
                else
                    x += sx;

                error += 2 * dy;
            }
        }
    }

    return pixels;
}

std::vector <pixel_t> bresenham_smooth(point_t start, point_t end)
{
    return bresenham_smooth(start, end, 255);
}

std::vector <pixel_t> bresenham_smooth(point_t start, point_t end, double max_intensity)
{
    std::vector<pixel_t> pixels;

    if (start.x == end.x && start.y == end.y)
        pixels.push_back(pixel_create((int)round(start.x), (int)round(start.y)));
    else
    {
        int x = start.x;
        int y = start.y;

        int dx = (end.x - start.x);
        int dy = (end.y - start.y);

        int sx = sign(dx);
        int sy = sign(dy);

        dx = abs(dx);
        dy = abs(dy);

        bool exchange = false;

        if (dy > dx)
        {
            std::swap(dx, dy);
            exchange = true;
        }

        double m = max_intensity * dy / dx;
        double error = max_intensity / 2;
        double w = max_intensity - m;

        for (int i = 0; i < dx; i++)
        {
            pixels.push_back(pixel_create(x, y, round(error)));

            if (error < w)
            {
                if (exchange)
                    y += sy;
                else
                    x += sx;

                error += m;
            }
            else
            {
                x += sx;
                y += sy;
                error -= w;
            }
        }
    }

    return pixels;
}
