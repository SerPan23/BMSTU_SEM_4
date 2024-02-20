#ifndef DRAW_SCREEN_H
#define DRAW_SCREEN_H

#include "shape.h"
#include "figure.h"
#include <QPainter>>

struct draw_view
{
    QPixmap *scene;
    QPainter *painter;
    double width;
    double height;
};

using draw_view_t = struct draw_view;

void draw(draw_view_t *view, figure_t *figure);

#endif // DRAW_SCREEN_H
