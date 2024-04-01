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

void draw_circle(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, double &radius);
void draw_ellipse(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, point_t &radius);

#endif // DRAW_H
