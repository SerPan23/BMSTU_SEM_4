#include "algorithms.h"

static double fpart(double x)
{
    return x - floor(x);
}

static double rfpart(double x)
{
    return 1 - fpart(x);
}

line_t wu(point_t start, point_t end)
{
    return wu(start, end, 255);
}

line_t wu(point_t start, point_t end, double max_intensity)
{
    std::vector<pixel_t> pixels;

    if (start.x == end.x && start.y == end.y)
        pixels.push_back(pixel_create((int)round(start.x), (int)round(start.y)));
    else
    {
        bool steep = abs(end.y - start.y) > abs(end.x - start.x);

        if (steep) {
            double buf = start.x;
            start.x = start.y;
            start.y = buf;

            buf = end.x;
            end.x = end.y;
            end.y = buf;
        }

        if (start.x > end.x) {
            double buf = start.x;
            start.x = end.x;
            end.x = buf;

            buf = end.y;
            end.y = start.y;
            start.y = buf;
        }

        double dx = end.x - start.x;
        double dy = end.y - start.y;

        double gradient;

        if (abs(dx) < EPS)
            gradient = 1.0;
        else
            gradient = dy / dx;


        // handle first endpoint
        double xend = round(start.x);
        double yend = start.y + gradient * (xend - start.x);
        double xgap = rfpart(start.x + 0.5);

        double xpxl1 = xend; // this will be used in the main loop
        double ypxl1 = floor(yend);

        if (steep)
        {
            pixels.push_back(pixel_create(ypxl1, xpxl1, rfpart(yend) * xgap * max_intensity));
            pixels.push_back(pixel_create(ypxl1 + 1, xpxl1, fpart(yend) * xgap * max_intensity));
        }
        else
        {
            pixels.push_back(pixel_create(xpxl1, ypxl1  , rfpart(yend) * xgap * max_intensity));
            pixels.push_back(pixel_create(xpxl1, ypxl1 + 1,  fpart(yend) * xgap * max_intensity));
        }

        double intery = yend + gradient; // first y-intersection for the main loop

        // handle second endpoint
        xend = round(end.x);
        yend = end.y + gradient * (xend - end.x);
        xgap = fpart(end.x + 0.5);

        double xpxl2 = xend; //this will be used in the main loop
        double ypxl2 = floor(yend);

        if (steep)
        {
            pixels.push_back(pixel_create(ypxl2  , xpxl2, rfpart(yend) * xgap * max_intensity));
            pixels.push_back(pixel_create(ypxl2 + 1, xpxl2,  fpart(yend) * xgap * max_intensity));
        }
        else
        {
            pixels.push_back(pixel_create(xpxl2, ypxl2,  rfpart(yend) * xgap * max_intensity));
            pixels.push_back(pixel_create(xpxl2, ypxl2 + 1, fpart(yend) * xgap * max_intensity));
        }

        int sx = sign(xpxl2 - xpxl1);

        // main loop
        if (steep)
        {
            for (int x = xpxl1 + 1; x != xpxl2; x += sx)
            {
                pixels.push_back(pixel_create(floor(intery)  , x, rfpart(intery) * max_intensity));
                pixels.push_back(pixel_create(floor(intery) + 1, x,  fpart(intery) * max_intensity));
                intery += gradient;
            }
        }
        else
        {
            for (int x = xpxl1 + 1; x != xpxl2; x += sx)
            {
                pixels.push_back(pixel_create(x, floor(intery),  rfpart(intery) * max_intensity));
                pixels.push_back(pixel_create(x, floor(intery) + 1, fpart(intery) * max_intensity));
                intery += gradient;
            }
        }
    }

    return line_t{pixels};
}


int wu_step_count(point_t start, point_t end)
{
    if (start.x == end.x && start.y == end.y)
        return 0;

    double max_intensity = 255;

    bool steep = abs(end.y - start.y) > abs(end.x - start.x);

    if (steep) {
        double buf = start.x;
        start.x = start.y;
        start.y = buf;

        buf = end.x;
        end.x = end.y;
        end.y = buf;
    }

    if (start.x > end.x) {
        double buf = start.x;
        start.x = end.x;
        end.x = buf;

        buf = end.y;
        end.y = start.y;
        start.y = buf;
    }

    double dx = end.x - start.x;
    double dy = end.y - start.y;

    double gradient;

    if (abs(dx) < EPS)
        gradient = 1.0;
    else
        gradient = dy / dx;


    // handle first endpoint
    double xend = round(start.x);
    double yend = start.y + gradient * (xend - start.x);

    double xpxl1 = xend; // this will be used in the main loop
    double ypxl1 = floor(yend);

    double intery = yend + gradient; // first y-intersection for the main loop

    // handle second endpoint
    xend = round(end.x);

    double xpxl2 = xend; //this will be used in the main loop



    bool is_prev = false;
    int x_prev = steep ? ypxl1 : xpxl1;
    int steps = 1;

    for (int x = xpxl1; x <= xpxl2; x++)
    {
        if (x_prev != floor(intery))
            steps++;

        x_prev = floor(intery);
        intery += gradient;
    }

    return steps;
}
