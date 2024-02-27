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


void point_set_default(point_t &point);

void point_move(point_t &point, move_data_t &coeff);
void point_rotate(point_t &point, point_t &rotate_center, rotate_data_t &coeff);
void point_scale(point_t &point, point_t &scale_center, scale_data_t &coeff);

return_codes_t point_fread(point_t &point, FILE *in);
return_codes_t point_fwrite(point_t &point, FILE *out);

#endif // POINT_H
