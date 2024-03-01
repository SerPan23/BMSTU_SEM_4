#ifndef POINTS_H
#define POINTS_H

#include "point.h"
#include "return_codes.h"

struct points
{
    point_t *data;
    int size;
};

using points_t = struct points;

return_codes_t points_alloc(points_t &points);
void points_free(points_t &points);

points_t points_set_default();

return_codes_t points_move_all(points_t &points, const move_data_t &coeff);
return_codes_t points_rotate_all(points_t &points, const point_t &rotate_center, const rotate_data_t &coeff);
return_codes_t points_scale_all(points_t &points, const point_t &scale_center, const scale_data_t &coeff);

return_codes_t points_fread(points_t &points, FILE *in);
return_codes_t points_fwrite(const points_t &points, FILE *out);

#endif // POINTS_H
