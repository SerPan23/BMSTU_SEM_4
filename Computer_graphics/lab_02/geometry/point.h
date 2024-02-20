#ifndef POINT_H
#define POINT_H

#include <cstdlib>
#include <cmath>

struct point
{
    double x;
    double y;
};

using point_t = struct point;


point_t *point_create(double x, double y);
void point_free(point_t **point);

void point_set_default(point_t *point);
point_t *point_move(point_t * point, point_t *offset);
point_t *point_rotate(point_t * point, point_t *rotate_center, int angel);
point_t *point_scale(point_t * point, point_t *scale_center, point_t *scale);


#endif // POINT_H
