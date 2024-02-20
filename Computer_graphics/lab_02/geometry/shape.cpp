#include "shape.h"

shape_t *shape_create(point_t *point)
{
    shape_t *shape = (shape_t *) malloc(sizeof(shape_t));
    if (shape == NULL)
        return NULL;

    shape->type = POINT;
    shape->shape.point = point;

    return shape;
}

shape_t *shape_create(line_t *line)
{
    shape_t *shape = (shape_t *) malloc(sizeof(shape_t));
    if (shape == NULL)
        return NULL;

    shape->type = LINE;
    shape->shape.line = line;

    return shape;
}

shape_t *shape_create(ellipse_t *ellipse)
{
    shape_t *shape = (shape_t *) malloc(sizeof(shape_t));
    if (shape == NULL)
        return NULL;

    shape->type = ELLIPSE;
    shape->shape.ellipse = ellipse;

    return shape;
}

shape_t *shape_create(arc_t *arc)
{
    shape_t *shape = (shape_t *) malloc(sizeof(shape_t));
    if (shape == NULL)
        return NULL;

    shape->type = ARC;
    shape->shape.arc = arc;

    return shape;
}

void shape_free(shape_t **shape)
{
    if (*shape)
    {
        switch ((*shape)->type)
        {
        case POINT:
            point_free(&(*shape)->shape.point);
            break;

        case ARC:
            arc_free(&(*shape)->shape.arc);
            break;

        case ELLIPSE:
            ellipse_free(&(*shape)->shape.ellipse);
            break;

        case LINE:
            line_free(&(*shape)->shape.line);
            break;
        }

        free(*shape);
    }

    *shape = NULL;
}

shape_t *shape_move(shape_t *shape, point_t *offset)
{
    shape_t *new_shape = NULL;
    switch (shape->type)
    {
    case POINT:
        new_shape = shape_create(point_move(shape->shape.point, offset));
        break;

    case ARC:
        new_shape = shape_create(arc_move(shape->shape.arc, offset));
        break;

    case ELLIPSE:
        new_shape = shape_create(ellipse_move(shape->shape.ellipse, offset));
        break;

    case LINE:
        new_shape = shape_create(line_move(shape->shape.line, offset));
        break;
    }

    return new_shape;
}

shape_t *shape_rotate(shape_t *shape, point_t *rotate_center, int angel)
{
    shape_t *new_shape = NULL;
    switch (shape->type)
    {
    case POINT:
        new_shape = shape_create(point_rotate(shape->shape.point, rotate_center, angel));
        break;

    case ARC:
        new_shape = shape_create(arc_rotate(shape->shape.arc, rotate_center, angel));
        break;

    case ELLIPSE:
        new_shape = shape_create(ellipse_rotate(shape->shape.ellipse, rotate_center, angel));
        break;

    case LINE:
        new_shape = shape_create(line_rotate(shape->shape.line, rotate_center, angel));
        break;
    }

    return new_shape;
}

shape_t *shape_scale(shape_t *shape, point_t *scale_center, point_t *scale)
{
    shape_t *new_shape = NULL;
    switch (shape->type)
    {
    case POINT:
        new_shape = shape_create(point_scale(shape->shape.point, scale_center, scale));
        break;

    case ARC:
        new_shape = shape_create(arc_scale(shape->shape.arc, scale_center, scale));
        break;

    case ELLIPSE:
        new_shape = shape_create(ellipse_scale(shape->shape.ellipse, scale_center, scale));
        break;

    case LINE:
        new_shape = shape_create(line_scale(shape->shape.line, scale_center, scale));
        break;
    }

    return new_shape;
}
