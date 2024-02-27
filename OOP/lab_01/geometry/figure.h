#ifndef FIGURE_H
#define FIGURE_H

#include "return_codes.h"
#include "request_data.h"
#include "point.h"
#include "points.h"
#include "edges.h"

struct figure
{
    point_t center;
    points_t points;
    edges_t edges;
};

using figure_t = struct figure;

figure_t &figure_create(void);
void figure_free(figure_t &figure);


return_codes_t figure_move(figure_t &figure, move_data_t &coeff);
return_codes_t figure_rotate(figure_t &figure, rotate_data_t &coeff);
return_codes_t figure_scale(figure_t &figure, scale_data_t &coeff);

return_codes_t figure_load(figure_t &figure, char *filename);
return_codes_t figure_save(figure_t &figure, char *filename);

#endif // FIGURE_H
