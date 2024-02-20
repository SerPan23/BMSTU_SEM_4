#ifndef ARC_H
#define ARC_H

#include "point.h"
#include "rectangle.h"

struct arc
{
    rectangle_t *rect;
    int start_ang;
    double span_ang;
};

using arc_t = struct arc;

arc_t *arc_create(rectangle_t *rect, int start_ang, int span_ang);
void arc_free(arc_t **arc);

int angle_rotate(int angle, int angle_rot);

arc_t *arc_move(arc_t *arc, point_t *offset);
arc_t *arc_rotate(arc_t *arc, point_t *rotate_center, int angel);
arc_t *arc_scale(arc_t *arc, point_t *scale_center, point_t *scale);

#endif // ARC_H
