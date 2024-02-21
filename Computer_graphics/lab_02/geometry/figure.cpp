#include "figure.h"

void figure_free(figure_t *figure)
{
    point_free(&figure->center);
    shapes_free(&figure->shapes);
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
