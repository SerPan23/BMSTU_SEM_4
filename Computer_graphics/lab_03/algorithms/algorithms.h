#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cmath>
#include <vector>
#include <iostream>

#define sign(x)  (signbit(x) ?  -1 : 1)

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

pixel_t pixel_create(int x, int y);
pixel_t pixel_create(int x, int y, double intensity);

std::vector <pixel_t> dda(point_t start, point_t end);

std::vector <pixel_t> bresenham_double(point_t start, point_t end);
std::vector <pixel_t> bresenham_integer(point_t start, point_t end);
std::vector <pixel_t> bresenham_smooth(point_t start, point_t end);
std::vector <pixel_t> bresenham_smooth(point_t start, point_t end, double max_intensity);

std::vector <pixel_t> wu(point_t start, point_t end);
std::vector <pixel_t> wu(point_t start, point_t end, double max_intensity);

#endif // ALGORITHMS_H
