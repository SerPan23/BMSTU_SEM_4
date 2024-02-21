#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include "line.h"
#include "ellipse.h"
#include "arc.h"

enum shape_type
{
    POINT,
    ARC,
    ELLIPSE,
    LINE,
};

using shape_type_t = enum shape_type;

struct shape
{
    shape_type_t type;
    union
    {
        point_t *point;
        line_t *line;
        ellipse_t *ellipse;
        arc_t *arc;
    } shape;
};

using shape_t = struct shape;

shape_t *shape_create(point_t *point);
shape_t *shape_create(line_t *line);
shape_t *shape_create(ellipse_t *ellipse);
shape_t *shape_create(arc_t *arc);

void shape_free(shape_t **shape);

shape_t *shape_move(shape_t * shape, point_t *offset);
shape_t *shape_rotate(shape_t * shape, point_t *rotate_center, double angel);
shape_t *shape_scale(shape_t * shape, point_t *scale_center, point_t *scale);

#endif // SHAPE_H
