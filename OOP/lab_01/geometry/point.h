#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "request_data.h"
#include "return_codes.h"

struct point
{
    double x;
    double y;
    double z;
};

using point_t = struct point;


point_t point_set_default();

return_codes_t point_move(point_t &point, const move_data_t &coeff);
return_codes_t point_rotate(point_t &point, const point_t &rotate_center, const rotate_data_t &coeff);
return_codes_t point_scale(point_t &point, const point_t &scale_center, const scale_data_t &coeff);

return_codes_t point_fread(point_t &point, FILE *in);
return_codes_t point_fwrite(const point_t &point, FILE *out);

#endif // POINT_H
