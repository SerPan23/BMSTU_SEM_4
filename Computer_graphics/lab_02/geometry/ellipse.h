#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "rectangle.h"

// struct ellipse
// {
//     rectangle_t *rect;
// };

struct ellipse
{
    point_t *center;
    double radius_x;
    double radius_y;
    point_t *scale;
    double rotate_angle;
};

using ellipse_t = struct ellipse;

// ellipse_t *ellipse_create(rectangle_t *rect);
ellipse_t *ellipse_create(point_t *center, double radius_x, double radius_y);
void ellipse_free(ellipse_t **ellipse);

ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset);
ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, double angel);
ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale);

#endif // ELLIPSE_H
