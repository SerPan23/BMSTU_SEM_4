#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "rectangle.h"

struct ellipse
{
    rectangle_t *rect;
};

using ellipse_t = struct ellipse;

ellipse_t *ellipse_create(rectangle_t *rect);
void ellipse_free(ellipse_t **ellipse);

ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset);
ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, int angel);
ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale);

#endif // ELLIPSE_H
