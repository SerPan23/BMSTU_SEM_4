#ifndef FIGURE_H
#define FIGURE_H

#include "shapes.h"

struct figure
{
    point_t *center;
    shapes_t shapes;
};

using figure_t = struct figure;

void figure_free(figure_t *figure);

figure_t figure_move(figure_t *figure, point_t *offset);
figure_t figure_rotate(figure_t *figure, point_t *rotate_center, int angel);
figure_t figure_scale(figure_t *figure, point_t *scale_center, point_t *scale);

#endif // FIGURE_H
