#include "point.h"

point_t *point_create(double x, double y)
{
    point_t *point = (point_t *) malloc(sizeof(point_t));
    if (point == NULL)
        return NULL;

    point->x = x;
    point->y = y;

    return point;
}

void point_free(point_t **point)
{
    if (*point)
        free(*point);

    *point = NULL;
}

void point_set_default(point_t *point)
{
    point->x = 0.0;
    point->y = 0.0;
}

point_t *point_move(point_t * point, point_t *offset)
{
    return point_create(
        point->x + offset->x,
        point->y + offset->y);
}

point_t *point_rotate(point_t * point, point_t *rotate_center, int angel)
{
    double angel_radian = angel;
    return point_create(
        rotate_center->x + (point->x - rotate_center->x) * cos(angel_radian)
            + (point->y - rotate_center->y) * sin(angel_radian),
        rotate_center->y - (point->x - rotate_center->x) * sin(angel_radian)
            + (point->y - rotate_center->y) * cos(angel_radian));
}

point_t *point_scale(point_t *point, point_t *scale_center, point_t *scale)
{
    return point_create(
        point->x * scale->x + scale_center->x * (1 - scale->x),
        point->y * scale->y + scale_center->y * (1 - scale->y));
}
