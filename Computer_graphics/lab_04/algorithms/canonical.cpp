#include "algorithms.h"
figure_t canonical_circle(point_t center, double radius)
{
    std::vector<pixel_t> pixels;

    double radius_sqr = radius * radius;

    int border = round(center.x + radius / sqrt(2));

    for (int x = center.x; x < border + 1; x++)
    {
        int h = (x - center.x) * (x - center.x);
        int y = center.y + sqrt(radius_sqr - h);
        pixels.push_back(pixel_create(x, y));
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

    for (int x = round(center.x); x < border_x + 1; x++)
    {
        int h = (x - center.x) * (x - center.x);
        int y = center.y + sqrt(radius_a_sqr * radius_b_sqr - h * radius_b_sqr) / radius.x;

        pixels.push_back(pixel_create(x, y));
    }

    int yc = round(center.y);
    for (int y = border_y; y > yc - 1; y--)
    {
        int h = (y - center.y) * (y - center.y);
        int x = center.x + sqrt(radius_a_sqr * radius_b_sqr - h * radius_a_sqr) / radius.y;

        pixels.push_back(pixel_create(x, y));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}
