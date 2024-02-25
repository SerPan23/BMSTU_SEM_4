#include "arc.h"

point_t *get_arc_point(point_t *center, double radius_x, double radius_y, double angle)
{
    return point_create(center->x + radius_x * cos(angle),
                        center->y + radius_y * sin(angle));
}

arc_t *arc_create(point_t *center, double radius_x, double radius_y, int start_ang, int span_ang)
{
    arc_t *arc = (arc_t *) malloc(sizeof(arc_t));
    if (arc == NULL)
        return NULL;

    double step = 1 / std::max(radius_x, radius_y) / 2;

    double start = to_rad(start_ang) + M_PI;
    double end = to_rad(start_ang + span_ang) + M_PI;

    for (double angle = start; angle <= end; angle += step)
        arc->points.push_back(get_arc_point(center, radius_x, radius_y, angle));

    return arc;
}

arc_t *arc_create(std::vector <point_t *> &points)
{
    arc_t *arc = (arc_t *) malloc(sizeof(arc_t));
    if (arc == NULL)
        return NULL;

    arc->points = points;

    return arc;
}

void arc_free(arc_t **arc)
{
    if (*arc)
    {
        // point_free(&(*arc)->center);
        for (int i = 0; i < (*arc)->points.size(); i++)
            point_free(&(*arc)->points[i]);
        free(*arc);
    }

    *arc = NULL;
}

arc_t *arc_move(arc_t *arc, point_t *offset)
{
    std::vector <point_t *> points;
    for (int i = 0; i < arc->points.size(); i++)
        points.push_back(point_move(arc->points[i], offset));
    return arc_create(points);
}

arc_t *arc_rotate(arc_t *arc, point_t *rotate_center, double angel)
{
    std::vector <point_t *> points;
    for (int i = 0; i < arc->points.size(); i++)
        points.push_back(point_rotate(arc->points[i], rotate_center, angel));
    return arc_create(points);
}

arc_t *arc_scale(arc_t *arc, point_t *scale_center, point_t *scale)
{
    std::vector <point_t *> points;
    for (int i = 0; i < arc->points.size(); i++)
        points.push_back(point_scale(arc->points[i], scale_center, scale));
    return arc_create(points);
}

void get_min_max_point(arc_t *a, point_t *pmin, point_t *pmax)
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
