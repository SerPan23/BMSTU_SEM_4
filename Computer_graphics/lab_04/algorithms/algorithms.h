#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cmath>
#include <vector>
#include <iostream>
#include <QString>
#include <QColor>


#include "point.h"
#include "pixel.h"

#define sign(x)  (signbit(x) ?  -1 : 1)
#define EPS 1e-8

#define ITER_COUNT_TIME 1000

enum algorithms
{
    CANONICAL,
    PARAMETRIC,
    BRESENHAM,
    MIDDLE_POINT,
    LIBRARY
};
using algorithm_t = enum algorithms;

algorithm_t get_algorithm(QString name);

struct figure
{
    std::vector<pixel_t> data;
    pixel_t center;
};
using figure_t = struct figure;

// circle
figure_t canonical_circle(point_t center, int radius);
figure_t parametric_circle(point_t center, int radius);
figure_t bresenham_circle(point_t center, int radius);
figure_t middle_point_circle(point_t center, int radius);

long time_measurement_circle(point_t center, int radius, figure_t (*alg)(point_t center, int radius));

// ellipse
figure_t canonical_ellipse(point_t center, point_t radius);
figure_t parametric_ellipse(point_t center, point_t radius);
figure_t bresenham_ellipse(point_t center, point_t radius);
figure_t middle_point_ellipse(point_t center, point_t radius);

long time_measurement_ellipse(point_t center, point_t radius, figure_t (*alg)(point_t center, point_t radius));

#endif // ALGORITHMS_H
