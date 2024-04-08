#include "algorithms.h"
figure_t canonical_circle(point_t center, int radius)
{
    std::vector<pixel_t> pixels;

    int radius_sqr = radius * radius;

    int border = round(center.x + radius / sqrt(2));

    for (int x = center.x; x < border + 1; x++)
    {
        double y = center.y + sqrt(radius_sqr - (x - center.x) * (x - center.x));
        pixels.push_back(pixel_create(x, (int)round(y)));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}

figure_t canonical_ellipse(point_t center, point_t radius)
{
    std::vector<pixel_t> pixels;

    double radius_a_sqr = radius.x * radius.x;
    double radius_b_sqr = radius.y * radius.y;

    int border_x = round(center.x + radius.x / sqrt(1 + radius_b_sqr / radius_a_sqr));
    int border_y = round(center.y + radius.y / sqrt(1 + radius_a_sqr / radius_b_sqr));

    for (int x = center.x; x < border_x + 1; x++)
    {
        double y = center.y + sqrt(radius_a_sqr * radius_b_sqr -
                                   (x - center.x) * (x - center.x) * radius_b_sqr) / (double) radius.x;

        pixels.push_back(pixel_create(x, (int)round(y)));
    }

    for (int y = center.y; y < border_y + 1; y++)
    {
        double x = center.x + sqrt(radius_a_sqr * radius_b_sqr -
                                   (y - center.y) * (y - center.y) * radius_a_sqr) / (double) radius.y;

        pixels.push_back(pixel_create((int)round(x), y));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}
