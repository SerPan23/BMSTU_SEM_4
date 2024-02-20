#ifndef SHAPES_H
#define SHAPES_H

#include <cstdlib>
#include "shape.h"

#define ERROR_MEM_ALLOC 2
#define ERROR_ARR_EMPTY 3
#define ERROR_INVALID_INDEX 4

struct shapes
{
    shape_t **data;
    size_t size;
    size_t size_alloced;
};

using shapes_t = struct shapes;

int shapes_alloc(shapes_t *shapes, size_t size);
void shapes_free(shapes_t *shapes);

int shapes_realloc(shapes_t *shapes, size_t new_size);

int shapes_push(shapes_t *shapes, shape_t *new_el);
int shapes_pop(shapes_t *shapes, size_t ind);
int shapes_clear(shapes_t *shapes);

shapes_t shapes_move(shapes_t *figure, point_t *offset);
shapes_t shapes_rotate(shapes_t *figure, point_t *rotate_center, int angel);
shapes_t shapes_scale(shapes_t *figure, point_t *scale_center, point_t *scale);

#endif // SHAPES_H
