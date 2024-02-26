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

struct line
{
    point_t first_point;
    point_t second_point;
};

using line_t = struct line;

point_t point_transform_to_screen(point_t point, draw_view_t &view);

line_t get_line(draw_view_t &view, edge_t &edge, point_t *array_points);

return_codes draw_line(draw_view_t &view, line_t &line);

return_codes draw_lines(draw_view_t &view, points_t &points, edges_t &edges);

return_codes draw_figure(figure_t &figure, draw_view_t &view);

return_codes scene_clear(draw_view_t &view);


#endif // DRAW_H
