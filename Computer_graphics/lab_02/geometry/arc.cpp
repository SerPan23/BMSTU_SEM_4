#include "arc.h"

arc_t *arc_create(rectangle_t *rect, int start_ang, int span_ang)
{
    arc_t *arc = (arc_t *) malloc(sizeof(arc_t));
    if (arc == NULL)
        return NULL;

    arc->rect = rect;
    arc->start_ang = start_ang;
    arc->span_ang = span_ang;

    return arc;
}

void arc_free(arc_t **arc)
{
    if (*arc)
    {
        rectangle_free(&(*arc)->rect);
        free(*arc);
    }

    *arc = NULL;
}

int angle_rotate(int angle, int angle_rot)
{
    // return (angle + angle_rot) % 360 * M_PI / 180;
    return (angle + angle_rot) % 360;
}

arc_t *arc_move(arc_t *arc, point_t *offset)
{
    return arc_create(
        rectangle_move(arc->rect, offset),
        arc->start_ang, arc->span_ang);
}

arc_t *arc_rotate(arc_t *arc, point_t *rotate_center, int angel)
{
    return arc_create(
        rectangle_rotate(arc->rect, rotate_center, angel),
        angle_rotate(arc->start_ang, angel),
        angle_rotate(arc->span_ang, angel));
}

arc_t *arc_scale(arc_t *arc, point_t *scale_center, point_t *scale)
{
    return arc_create(
        rectangle_scale(arc->rect, scale_center, scale),
        arc->start_ang, arc->span_ang);
}
