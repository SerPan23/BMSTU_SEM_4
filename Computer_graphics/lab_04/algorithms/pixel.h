#ifndef PIXEL_H
#define PIXEL_H

#include "point.h"

struct pixel
{
    int x;
    int y;
    double intensity;
};

using pixel_t = struct pixel;

pixel_t pixel_create(int x, int y);
pixel_t pixel_create(int x, int y, double intensity);
pixel_t pixel_create(point_t point);

#endif // PIXEL_H
