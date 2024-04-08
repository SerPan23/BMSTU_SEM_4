#ifndef DRAW_H
#define DRAW_H

#include <QPainter>

#include "figure.h"

struct draw_view
{
    QPixmap *scene;
    double width;
    double height;
};

using draw_view_t = struct draw_view;

void draw_line(draw_view_t& view, QColor& color, Point& start, Point& end);
void draw_figure(draw_view_t& view, QColor& color, Figure& figure);

#endif // DRAW_H
