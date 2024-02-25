#include "ellipse.h"

point_t *get_ellipse_point(point_t *center, double radius_x, double radius_y, double angle)
{
    return point_create(
            center->x + radius_x * cos(angle),
            center->y + radius_y * sin(angle));
}

ellipse_t *ellipse_create(point_t *center, double radius_x, double radius_y)
{
    ellipse_t *ellipse = (ellipse_t *) malloc(sizeof(ellipse_t));
    if (ellipse == NULL)
        return NULL;

    // ellipse->center = center;

    // ellipse->radius_x = radius_x;
    // ellipse->radius_y = radius_y;


    double step = 1 / std::max(radius_x, radius_y) / 2;

    for (double angle = 0; angle <= 2 * M_PI; angle += step)
        ellipse->points.push_back(
            get_ellipse_point(center, radius_x, radius_y, angle));

    return ellipse;
}

ellipse_t *ellipse_empty_create()
{
    ellipse_t *ellipse = (ellipse_t *) malloc(sizeof(ellipse_t));
    if (ellipse == NULL)
        return NULL;

    return ellipse;
}

void ellipse_free(ellipse_t **ellipse)
{
    if (*ellipse)
    {
        // point_free(&(*ellipse)->center);
        for (int i = 0; i < (*ellipse)->points.size(); i++)
            point_free(&(*ellipse)->points[i]);
        free(*ellipse);
    }

    *ellipse = NULL;
}


ellipse_t *ellipse_move(ellipse_t *ellipse, point_t *offset)
{
    ellipse_t * tmp = ellipse_empty_create();
    for (int i = 0; i < ellipse->points.size(); i++)
        tmp->points.push_back(point_move(ellipse->points[i], offset));
    return tmp;
}

ellipse_t *ellipse_rotate(ellipse_t *ellipse, point_t *rotate_center, double angel)
{
    ellipse_t *tmp = ellipse_empty_create();
    for (int i = 0; i < ellipse->points.size(); i++)
        tmp->points.push_back(point_rotate(ellipse->points[i], rotate_center, angel));
    return tmp;
}

ellipse_t *ellipse_scale(ellipse_t *ellipse, point_t *scale_center, point_t *scale)
{
    ellipse_t *tmp = ellipse_empty_create();
    for (int i = 0; i < ellipse->points.size(); i++)
        tmp->points.push_back(point_scale(ellipse->points[i], scale_center, scale));
    return tmp;
}

void get_min_max_point(ellipse_t *a, point_t *pmin, point_t *pmax)
{
    pmin->x = std::fmin(pmin->x, a->points[0]->x);
    pmin->y = std::fmin(pmin->y, a->points[0]->y);
    pmax->x = std::fmax(pmax->x, a->points[0]->x);
    pmax->y = std::fmax(pmax->y, a->points[0]->y);

    for (int i = 1; i < a->points.size(); i++)
    {
        pmin->x = std::fmin(pmin->x, a->points[i]->x);
        pmin->y = std::fmin(pmin->y, a->points[i]->y);

        pmax->x = std::fmax(pmax->x, a->points[i]->x);
        pmax->y = std::fmax(pmax->y, a->points[i]->y);
    }
}
