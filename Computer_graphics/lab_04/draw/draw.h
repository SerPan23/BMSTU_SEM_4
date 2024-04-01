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

void draw_line(draw_view_t *view, QColor color, point_t start, point_t end);
void draw_line(draw_view_t *view, QColor color, line_t line);

#endif // DRAW_H
