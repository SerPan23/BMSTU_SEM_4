#include "ellipse.h"


ellipse_t *ellipse_create(point_t *center, double radius_x, double radius_y)
{
    ellipse_t *ellipse = (ellipse_t *) malloc(sizeof(ellipse_t));
    if (ellipse == NULL)
        return NULL;

    ellipse->center = center;

    ellipse->radius_x = radius_x;
    ellipse->radius_y = radius_y;

    return ellipse;
}

void ellipse_free(ellipse_t **ellipse)
{
    if (*ellipse)
    {
        point_free(&(*ellipse)->center);
        free(*ellipse);
    }

    *ellipse = NULL;
}


ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset)
{
    return ellipse_create(point_move(ellipse->center, offset),
                          ellipse->radius_x, ellipse->radius_y);
}

ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, double angel)
{
    return ellipse_create(point_rotate(ellipse->center, rotate_center, angel),
                          ellipse->radius_x, ellipse->radius_y);
}

ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale)
{
    return ellipse_create(point_scale(ellipse->center, scale_center, scale),
                          ellipse->radius_x, ellipse->radius_y);
}

// ellipse_t *ellipse_create(rectangle_t *rect)
// {
//     ellipse_t *ellipse = (ellipse_t *) malloc(sizeof(ellipse_t));
//     if (ellipse == NULL)
//         return NULL;

//     ellipse->rect = rect;

//     return ellipse;
// }

// void ellipse_free(ellipse_t **ellipse)
// {
//     if (*ellipse)
//     {
//         rectangle_free(&(*ellipse)->rect);
//         free(*ellipse);
//     }

//     *ellipse = NULL;
// }


// ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset)
// {
//     return ellipse_create(rectangle_move(ellipse->rect, offset));
// }

// ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, double angel)
// {
//     return ellipse_create(rectangle_rotate(ellipse->rect, rotate_center, angel));
// }

// ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale)
// {
//     return ellipse_create(rectangle_scale(ellipse->rect, scale_center, scale));
// }
