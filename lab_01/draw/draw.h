#ifndef DRAW_H
#define DRAW_H

#include "return_codes.h"
#include "point.h"
#include "points.h"
#include "triangle.h"
#include <QPainter>

#define BORDER_K 1.1

struct draw_view
{
    QPixmap *scene;
    QPainter *painter;
    double width;
    double height;
};

using draw_view_t = struct draw_view;

return_codes_t clear_scene(const draw_view_t *view);

point_t *get_normalized(point_t *p, draw_view_t *view, point_t *pmin, point_t *pmax);
void transfom_min_max(draw_view_t *view, point_t *pmin, point_t *pmax);

return_codes_t draw_line(draw_view_t *view, point_t *p1, point_t *p2);
return_codes_t draw_point(draw_view_t *view, point_t *p1);

return_codes_t draw_result(draw_view_t *view, triangle_t *triangle, point_t *pab, point_t *pbb, point_t *pcb, point_t *pcenters);

#endif // DRAW_H
