#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

#include "return_codes.h"
#include "figure.h"
#include "point.h"

struct draw_view
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using draw_view_t = struct draw_view;

return_codes draw_figure(figure_t &figure, draw_view_t &view);

return_codes scene_clear(draw_view_t &view);


#endif // DRAW_H
