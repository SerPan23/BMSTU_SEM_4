#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "algorithms.h"

struct draw_view
{
    QPixmap *scene;
    double width;
    double height;
};

using draw_view_t = struct draw_view;

void draw_circle(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, int &radius);
void draw_ellipse(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, point_t &radius);


struct spectrum_data
{
    QColor color;
    point_t center;
    point_t start_radius;
    int step;
    int figures_count;
};

using spectrum_data_t = struct spectrum_data;

void draw_circles_spectrum(draw_view_t& view, algorithm_t &alg, spectrum_data_t& spectrum_data);
void draw_ellipses_spectrum(draw_view_t& view, algorithm_t &alg, spectrum_data_t& spectrum_data);

#endif // DRAW_H
