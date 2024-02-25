#include "figure.h"
#include <ostream>

void figure_free(figure_t *figure)
{
    point_free(&figure->center);
    shapes_free(&figure->shapes);
}

void figure_find_and_set_center(figure_t *figure)
{
    point_t *pmin = point_create(0, 0), *pmax = point_create(0, 0);

    bool flag = true;

    for (int i = 0; i < figure->shapes.size; i++)
    {
        if (flag)
        {
            flag = false;
            switch (figure->shapes.data[i]->type)
            {
            case POINT:
                pmin->x = figure->shapes.data[i]->shape.point->x;
                pmin->y = figure->shapes.data[i]->shape.point->y;
                break;

            case ARC:
                pmin->x = figure->shapes.data[i]->shape.arc->points[0]->x;
                pmin->y = figure->shapes.data[i]->shape.arc->points[0]->y;
                break;

            case ELLIPSE:
                pmin->x = figure->shapes.data[i]->shape.ellipse->points[0]->x;
                pmin->y = figure->shapes.data[i]->shape.ellipse->points[0]->y;
                break;

            case LINE:
                pmin->x = figure->shapes.data[i]->shape.line->start->x;
                pmin->y = figure->shapes.data[i]->shape.line->start->y;
                break;
            }
        }
        get_min_max_point(figure->shapes.data[i], pmin, pmax);
    }

    point_t *p1 = point_create(pmin->x, pmax->y), *p2 = point_create(pmax->x, pmin->y);

    line_t *a = line_create(pmin, pmax);
    line_t *b = line_create(p1, p2);

    figure->center = get_lines_cross(a, b);
    line_free(&a);
    line_free(&b);
}

figure_t figure_move(figure_t *figure, point_t *offset)
{
    figure_t new_figure;
    new_figure.center = point_move(figure->center, offset);

    new_figure.shapes = shapes_move(&figure->shapes, offset);

    return new_figure;
}

figure_t figure_rotate(figure_t *figure, point_t *rotate_center, double angel)
{
    figure_t new_figure;
    new_figure.center = point_rotate(figure->center, rotate_center, angel);

    new_figure.shapes = shapes_rotate(&figure->shapes, rotate_center, angel);

    return new_figure;
}

figure_t figure_scale(figure_t *figure, point_t *scale_center, point_t *scale)
{
    figure_t new_figure;
    new_figure.center = point_scale(figure->center, scale_center, scale);

    new_figure.shapes = shapes_scale(&figure->shapes, scale_center, scale);

    return new_figure;
}
