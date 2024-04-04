#include "algorithms.h"
figure_t middle_point_circle(point_t center, int radius)
{
    std::vector<pixel_t> pixels;

    int x = radius;
    int y = 0;

    pixels.push_back(pixel_create(x + center.x, y + center.y));

    int delta = 1 - radius;

    while (x >= y)
    {
        if (delta >= 0)
        {
            x -= 1;
            y += 1;
            delta += 2 * y + 1 - 2 * x;
        }
        else
        {
            y += 1;
            delta += 2 * y + 1;
        }

        pixels.push_back(pixel_create(x + center.x, y + center.y));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}

figure_t middle_point_ellipse(point_t center, point_t radius)
{
    std::vector<pixel_t> pixels;

    int sqr_ra = radius.x * radius.x;
    int sqr_rb = radius.y * radius.y;

    int x = 0;
    int y = radius.y;

    pixels.push_back(pixel_create(x + center.x, y + center.y));

    int border = round(radius.x / sqrt(1.0 + sqr_rb * 1.0 / sqr_ra));
    int delta = sqr_rb - (int)round(sqr_ra * (radius.y - 1.0 / 4));

    while (x <= border)
    {
        if (delta < 0)
        {
            x += 1;
            delta += 2 * sqr_rb * x + 1;
        }
        else
        {
            x += 1;
            y -= 1;
            delta += 2 * sqr_rb * x - 2 * sqr_ra * y + 1;
        }

        pixels.push_back(pixel_create(x + center.x, y + center.y));
    }

    x = radius.x;
    y = 0;

    pixels.push_back(pixel_create(x + center.x, y + center.y));

    border = round(radius.y / sqrt(1 + sqr_ra * 1.0 / sqr_rb));
    delta = sqr_ra - (int)round(sqr_rb * (radius.x - 1.0 / 4));

    while (y <= border)
    {
        if (delta < 0)
        {
            y += 1;
            delta += 2 * sqr_ra * y + 1;
        }
        else
        {
            x -= 1;
            y += 1;
            delta += 2 * sqr_ra * y - 2 * sqr_rb * x + 1;
        }

        pixels.push_back(pixel_create(x + center.x, y + center.y));
    }


    return figure_t{pixels, pixel_create(center.x, center.y)};
}
