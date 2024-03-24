#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cmath>
#include <vector>
#include <iostream>

#define sign(x)  (signbit(x) ?  -1 : 1)
#define EPS 1e-8

struct point
{
    double x;
    double y;
};

using point_t = struct point;

struct pixel
{
    int x;
    int y;
    double intensity;
};

using pixel_t = struct pixel;

struct line
{
    std::vector <pixel_t> pixels;
};
using line_t = struct line;

pixel_t pixel_create(int x, int y);
pixel_t pixel_create(int x, int y, double intensity);

line_t dda(point_t start, point_t end);

line_t bresenham_double(point_t start, point_t end);
line_t bresenham_integer(point_t start, point_t end);
line_t bresenham_smooth(point_t start, point_t end);
line_t bresenham_smooth(point_t start, point_t end, double max_intensity);

line_t wu(point_t start, point_t end);
line_t wu(point_t start, point_t end, double max_intensity);

int count_steps(line_t line);

long time_measurement(point_t start, point_t end, line_t (*alg)(point_t start, point_t end));

#endif // ALGORITHMS_H
