#include "rectangle.h"

rectangle_t *rectangle_create(point_t *a, point_t *b, point_t *c, point_t *d)
{
    rectangle_t *rect = (rectangle_t *) malloc(sizeof(rectangle_t));
    if (rect == NULL)
        return NULL;

    rect->a = a;
    rect->b = b;
    rect->c = c;
    rect->d = d;

    return rect;
}

void rectangle_free(rectangle_t **rect)
{
    if (*rect)
    {
        point_free(&(*rect)->a);
        point_free(&(*rect)->b);
        point_free(&(*rect)->c);
        point_free(&(*rect)->d);
        free(*rect);
    }

    *rect = NULL;
}

rectangle_t *rectangle_move(rectangle_t * rect, point_t *offset)
{
    return rectangle_create(
        point_move(rect->a, offset),
        point_move(rect->b, offset),
        point_move(rect->c, offset),
        point_move(rect->d, offset));
}

rectangle_t *rectangle_rotate(rectangle_t * rect, point_t *rotate_center, double angel)
{
    return rectangle_create(
        point_rotate(rect->a, rotate_center, angel),
        point_rotate(rect->b, rotate_center, angel),
        point_rotate(rect->c, rotate_center, angel),
        point_rotate(rect->d, rotate_center, angel));
}

rectangle_t *rectangle_scale(rectangle_t * rect, point_t *scale_center, point_t *scale)
{
    return rectangle_create(
        point_scale(rect->a, scale_center, scale),
        point_scale(rect->b, scale_center, scale),
        point_scale(rect->c, scale_center, scale),
        point_scale(rect->d, scale_center, scale));
}
