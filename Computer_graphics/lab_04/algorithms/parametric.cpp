#include "algorithms.h"

figure_t parametric_circle(point_t center, int radius)
{
    std::vector<pixel_t> pixels;

    double step = 1.0 / radius;

    double i = 0;
    while (i <= M_PI / 4 + step)
    {
        double x = center.x + radius * cos(i);
        double y = center.y + radius * sin(i);
        pixels.push_back(pixel_create(x, y));

        i += step;
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}

figure_t parametric_ellipse(point_t center, point_t radius)
{
    std::vector<pixel_t> pixels;

    double step;
    if (radius.x > radius.y)
        step = 1.0 / radius.x;
    else
        step = 1.0 / radius.y;

    double i = 0;
    while (i <= M_PI / 2 + step)
    {
        double x = center.x + radius.x * cos(i);
        double y = center.y + radius.y * sin(i);
        pixels.push_back(pixel_create((int)round(x), (int)round(y)));

        i += step;
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}
