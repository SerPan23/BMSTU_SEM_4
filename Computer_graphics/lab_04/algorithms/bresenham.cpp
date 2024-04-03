#include "algorithms.h"
figure_t bresenham_circle(point_t center, double radius)
{
    std::vector<pixel_t> pixels;


    // int x = 0;
    // int y = radius;
    // int delta = 1 - 2 * radius;
    // int error = 0;
    // while(y >= 0)
    // {
    //     // setPixel(x0 + x, y0 + y);
    //     // setPixel(x0 + x, y0 - y);
    //     // setPixel(x0 - x, y0 + y);
    //     // setPixel(x0 - x, y0 - y);

    //     pixels.push_back(pixel_create(x + center.x, y + center.y));

    //     error = 2 * (delta + y) - 1;
    //     if(delta < 0 && error <= 0) {
    //         ++x;
    //         delta += 2 * x + 1;
    //         continue;
    //     }
    //     if(delta > 0 && error > 0) {
    //         --y;
    //         delta += 1 - 2 * y;
    //         continue;
    //     }
    //     ++x;
    //     delta += 2 * (x - y);
    //     --y;
    // }

    int x = 0;
    int y = radius;


    // draw_simetric_pixels(canvas, [x + xc, y + yc, colour], xc, yc, circle=True)
    pixels.push_back(pixel_create(x + center.x, y + center.y));

    int delta = 2 * (1 - radius);

    while (y >= x)
    {
        int d = 2 * (delta + y) - 1;
        x += 1;

        if (d >= 0)
        {
            y -= 1;
            delta += 2 * (x - y + 1);
        }
        else
            delta += x + x + 1;

        // draw_simetric_pixels(canvas, [x + xc, y + yc, colour], xc, yc, circle=True)
        pixels.push_back(pixel_create(x + center.x, y + center.y));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}

figure_t bresenham_ellipse(point_t center, point_t radius)
{
    std::vector<pixel_t> pixels;

    int x = 0;
    int y = radius.y;

    // if (draw)
        // draw_simetric_pixels(canvas, [x + xc, y + yc, colour], xc, yc, circle=False);
    pixels.push_back(pixel_create(x + center.x, y + center.y));

    int sqr_ra = radius.x * radius.x;
    int sqr_rb = radius.y * radius.y;
    int delta = sqr_rb - sqr_ra * (2 * radius.y + 1);

    while (y >= 0)
    {
        if (delta < 0)
        {
            int d1 = 2 * delta + sqr_ra * (2 * y + 2);

            x += 1;
            if (d1 < 0)
                delta += sqr_rb * (2 * x + 1);
            else
            {
                y -= 1;
                delta += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y);
            }

        }
        else if (delta > 0)
        {
            int d2 = 2 * delta + sqr_rb * (2 - 2 * x);

            y -= 1;
            if (d2 > 0)
                delta += sqr_ra * (1 - 2 * y);
            else
            {
                x += 1;
                delta += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y);
            }
        }
        else
        {
            y -= 1;
            x += 1;
            delta += sqr_rb * (2 * x + 1) + sqr_ra * (1 - 2 * y);
        }


        // if draw:
        // draw_simetric_pixels(canvas, [x + xc, y + yc, colour], xc, yc, circle=False)
        pixels.push_back(pixel_create(x + center.x, y + center.y));
    }

    return figure_t{pixels, pixel_create(center.x, center.y)};
}
