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
//     for (int y = start.y; y < end.y; y++)
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
//     double tan = dx / dy;

//     double y = start.y;
//     for (int x = start.x; x < end.x; x++)
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
//             int min_y = std::min(start.y, end.y);
//             int max_y = std::max(start.y, end.y);

//             for (int y = min_y; y < max_y; y++)
//                 pixels.push_back(pixel_create(start.x, y));
//         }
//         else if  (dy == 0)
//         {
//             int min_x = std::min(start.x, end.x);
//             int max_x = std::max(start.x, end.x);

//             for (int x = min_x; x < max_x; x++)
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

static double ipart(double x)
{
    return floor(x);
}

static double fpart(double x)
{
    return x - ipart(x);
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

    if (steep)
        std::swap(start, end);
    if (start.x > end.x)
        std::swap(start, end);


    double dx = end.y - start.x;
    double dy = end.y - start.y;

    double gradient;

    if (dx == 0.0)
        gradient = 1.0;
    else
        gradient = dy / dx;


    // handle first endpoint
    double xend = round(start.x);
    double yend = start.y + gradient * (xend - start.x);
    double xgap = rfpart(start.x + 0.5);
    double xpxl1 = xend; // this will be used in the main loop
    double ypxl1 = ipart(yend);
    if (steep)
    {
        pixels.push_back(pixel_create(ypxl1, xpxl1, rfpart(yend) * xgap * max_intensity));
        pixels.push_back(pixel_create(ypxl1 + 1, xpxl1, fpart(yend) * xgap * max_intensity));
    }
    else
    {
        pixels.push_back(pixel_create(xpxl1, ypxl1  , rfpart(yend) * xgap * max_intensity));
        pixels.push_back(pixel_create(xpxl1, ypxl1+1,  fpart(yend) * xgap * max_intensity));
    }

    double intery = yend + gradient; // first y-intersection for the main loop

    // handle second endpoint
    xend = round(end.x);
    yend = end.y + gradient * (xend - end.x);
    xgap = fpart(end.x + 0.5);
    double xpxl2 = xend; //this will be used in the main loop
    double ypxl2 = ipart(yend);
    if (steep)
    {
        pixels.push_back(pixel_create(ypxl2  , xpxl2, rfpart(yend) * xgap * max_intensity));
        pixels.push_back(pixel_create(ypxl2+1, xpxl2,  fpart(yend) * xgap * max_intensity));
    }
    else
    {
        pixels.push_back(pixel_create(xpxl2, ypxl2,  rfpart(yend) * xgap * max_intensity));
        pixels.push_back(pixel_create(xpxl2, ypxl2+1, fpart(yend) * xgap * max_intensity));
    }

    // main loop
    if (steep)
    {
        for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
        {
            pixels.push_back(pixel_create(ipart(intery)  , x, rfpart(intery) * max_intensity));
            pixels.push_back(pixel_create(ipart(intery)+1, x,  fpart(intery) * max_intensity));
            intery = intery + gradient;
        }
    }
    else
    {
        for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
        {
            pixels.push_back(pixel_create(x, ipart(intery),  rfpart(intery) * max_intensity));
            pixels.push_back(pixel_create(x, ipart(intery)+1, fpart(intery) * max_intensity));
            intery = intery + gradient;
        }
    }

    return line_t{pixels};
}
