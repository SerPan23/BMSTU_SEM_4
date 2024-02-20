#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"

struct rectangle
{
    point_t *a;
    point_t *b;
    point_t *c;
    point_t *d;
};

using rectangle_t = struct rectangle;

rectangle_t *rectangle_create(point_t *a, point_t *b, point_t *c, point_t *d);
void rectangle_free(rectangle_t **rectangle);

rectangle_t *rectangle_move(rectangle_t * rect, point_t *offset);
rectangle_t *rectangle_rotate(rectangle_t * rect, point_t *rotate_center, int angel);
rectangle_t *rectangle_scale(rectangle_t * rect, point_t *scale_center, point_t *scale);

#endif // RECTANGLE_H
