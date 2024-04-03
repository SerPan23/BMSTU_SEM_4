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

#define ITER_COUNT_TIME 100

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

struct spectrum_data
{
    QColor color;
    point_t center;
    point_t start_radius;
    int step;
    int figures_count;
};

using spectrum_data_t = struct spectrum_data;

struct figure
{
    std::vector<pixel_t> data;
    pixel_t center;
};
using figure_t = struct figure;

// circle
figure_t canonical_circle(point_t center, double radius);
figure_t parametric_circle(point_t center, double radius);
figure_t bresenham_circle(point_t center, double radius);
figure_t middle_point_circle(point_t center, double radius);

// long time_measurement_circle(point_t center, double radius, figure_t (*alg)(point_t center, double radius));
long time_measurement_circle(spectrum_data_t spectrum_data, figure_t (*alg)(point_t center, double radius));

// ellipse
figure_t canonical_ellipse(point_t center, point_t radius);
figure_t parametric_ellipse(point_t center, point_t radius);
figure_t bresenham_ellipse(point_t center, point_t radius);
figure_t middle_point_ellipse(point_t center, point_t radius);

// long time_measurement_ellipse(point_t center, point_t radius, figure_t (*alg)(point_t center, point_t radius));
long time_measurement_ellipse(spectrum_data_t spectrum_data, figure_t (*alg)(point_t center, point_t radius));

#endif // ALGORITHMS_H
