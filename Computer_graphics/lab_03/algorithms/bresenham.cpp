#include "algorithms.h"

line_t bresenham_double(point_t start, point_t end)
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

    return line_t{pixels};
}

int bresenham_double_step_count(point_t start, point_t end)
{
    if (start.x == end.x && start.y == end.y)
        return 0;

    int steps = 1;

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

    bool is_prev = false;
    int x_prev = 0;
    int y_prev = 0;

    for (int i = 0; i < dx; i++)
    {
        if (is_prev)
        {
            if (x != x_prev && y != y_prev)
                steps++;
        }
        else
            is_prev = true;

        // pixels.push_back(pixel_create(x, y));
        x_prev = x;
        y_prev = y;

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

    return steps;
}

line_t bresenham_integer(point_t start, point_t end)
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

    return line_t{pixels};
}


int bresenham_integer_step_count(point_t start, point_t end)
{
    if (start.x == end.x && start.y == end.y)
        return 0;

    int steps = 1;

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

    bool is_prev = false;
    int x_prev = 0;
    int y_prev = 0;

    for (int i = 0; i < dx; i++)
    {
        if (is_prev)
        {
            if (x != x_prev && y != y_prev)
                steps++;
        }
        else
            is_prev = true;

        // pixels.push_back(pixel_create(x, y));
        x_prev = x;
        y_prev = y;

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

    return steps;
}

line_t bresenham_smooth(point_t start, point_t end)
{
    return bresenham_smooth(start, end, 255);
}

line_t bresenham_smooth(point_t start, point_t end, double max_intensity)
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

    return line_t{pixels};
}

int bresenham_smooth_step_count(point_t start, point_t end)
{
    if (start.x == end.x && start.y == end.y)
        return 0;

    int steps = 1;

    double max_intensity = 255;

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

    bool is_prev = false;
    int x_prev = 0;
    int y_prev = 0;

    for (int i = 0; i < dx; i++)
    {
        if (is_prev)
        {
            if (x != x_prev && y != y_prev)
                steps++;
        }
        else
            is_prev = true;

        // pixels.push_back(pixel_create(x, y));
        x_prev = x;
        y_prev = y;

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

    return steps;
}
