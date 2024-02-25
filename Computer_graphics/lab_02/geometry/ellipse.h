#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "point.h"
#include "rectangle.h"

#include <vector>

struct ellipse
{
    // point_t *center;
    // double radius_x;
    // double radius_y;

    std::vector <point_t *> points;
};

using ellipse_t = struct ellipse;

// ellipse_t *ellipse_create(rectangle_t *rect);
ellipse_t *ellipse_create(point_t *center, double radius_x, double radius_y);
void ellipse_free(ellipse_t **ellipse);

ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset);
ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, double angel);
ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale);

point_t *get_ellipse_point(point_t *center, double radius_x, double radius_y, double angle);
void get_min_max_point(ellipse_t *a, point_t *pmin, point_t *pmax);

#endif // ELLIPSE_H
