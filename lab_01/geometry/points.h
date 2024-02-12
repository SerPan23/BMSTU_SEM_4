#ifndef POINTS_H
#define POINTS_H

#include <cstdlib>
#include "point.h"
#include "return_codes.h"

struct points
{
    point_t **data;
    size_t size;
    size_t size_alloced;
};

using points_t = struct points;

return_codes_t points_alloc(points_t *points, size_t size);
return_codes_t points_free(points_t *points);

return_codes_t points_realloc(points_t *points, size_t new_size);

return_codes_t points_push(points_t *points, point_t *new_el);
return_codes_t points_pop(points_t *points, size_t ind);

#endif // POINTS_H
