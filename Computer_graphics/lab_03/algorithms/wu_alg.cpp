#include "algorithms.h"

// line_t wu_x(point_t start, point_t end, double max_intensity)
// {
//     std::vector<pixel_t> pixels;

//     if (start.y > end.y)
//         std::swap(start, end);

//     double dx = end.x - start.x;
//     double dy = end.y - start.y;
//     double tan = dx / dy;

//     double x = start.x;
//     for (int y = round(start.y); y < round(end.y); y++)
//     {
//         double x_floor = floor(x);
//         double d_1 = x - x_floor;
//         double d_2 = 1 - d_1;
//         double int_1 = round(abs(d_1) * max_intensity);
//         double int_2 = round(abs(d_2) * max_intensity);

//         pixels.push_back(pixel_create(x_floor, y, int_2));
//         pixels.push_back(pixel_create(x_floor + 1, y, int_1));
//         x += tan;
//     }

//     return line_t{pixels};
// }

// line_t wu_y(point_t start, point_t end, double max_intensity)
// {
//     std::vector<pixel_t> pixels;

//     if (start.x > end.x)
//         std::swap(start, end);

//     double dx = end.x - start.x;
//     double dy = end.y - start.y;
//     double tan = dy / dx;

//     double y = start.y;
//     for (int x = round(start.x); x < round(end.x); x++)
//     {
//         double y_floor = floor(y);
//         double d_1 = y - y_floor;
//         double d_2 = 1 - d_1;
//         double int_1 = round(abs(d_1) * max_intensity);
//         double int_2 = round(abs(d_2) * max_intensity);

//         pixels.push_back(pixel_create(x, y_floor, int_2));
//         pixels.push_back(pixel_create(x, y_floor + 1, int_1));
//         y += tan;
//     }

//     return line_t{pixels};
// }

// line_t wu(point_t start, point_t end)
// {
//     return wu(start, end, 255);
// }

// line_t wu(point_t start, point_t end, double max_intensity)
// {
//     std::vector<pixel_t> pixels;

//     if (start.x == end.x && start.y == end.y)
//         pixels.push_back(pixel_create((int)round(start.x), (int)round(start.y)));
//     else
//     {
//         double dx = abs(end.x - start.x);
//         double dy = abs(end.y - start.y);

//         if (dx == 0)
//         {
//             double min_y = std::min(start.y, end.y);
//             double max_y = std::max(start.y, end.y);

//             for (int y = round(min_y); y < round(max_y); y++)
//                 pixels.push_back(pixel_create(start.x, y));
//         }
//         else if  (dy == 0)
//         {
//             double min_x = std::min(start.x, end.x);
//             double max_x = std::max(start.x, end.x);

//             for (int x = round(min_x); x < round(max_x); x++)
//                 pixels.push_back(pixel_create(x, start.y));
//         }
//         else if (dy >= dx)
//             return wu_x(start, end, max_intensity);
//         else
//             return wu_y(start, end, max_intensity);
//     }

//     return line_t{pixels};
// }


// SECOND VER

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

    return line_t{pixels};
}
