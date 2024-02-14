#include "points.h"

return_codes_t points_alloc(points_t *points, size_t size)
{
    point_t **tmp = (point_t **) malloc(size * sizeof(point_t*));
    if (tmp == NULL)
        return ERROR_MEM_ALLOC;

    points->data = tmp;
    points->size = 0;
    points->size_alloced = size;

    return SUCCESS;
}

return_codes_t points_free(points_t *points)
{
    for (size_t i = 0; i < points->size_alloced; i++)
        point_free(&points->data[i]);

    free(points->data);

    points->data = NULL;
    points->size = 0;
    points->size_alloced = 0;

    return SUCCESS;
}

return_codes_t points_realloc(points_t *points, size_t new_size)
{
    point_t **tmp = (point_t **) realloc(points->data, new_size * sizeof(point_t *));
    if (tmp == NULL)
        return ERROR_MEM_ALLOC;

    points->data = tmp;
    points->size_alloced = new_size;

    return SUCCESS;
}

return_codes_t points_push(points_t *points, point_t *new_el)
{
    if (points->size + 1 > points->size_alloced)
    {
        return_codes_t rc =  points_realloc(points, points->size_alloced + 1 + points->size_alloced * 0.1);

        if (rc != SUCCESS)
            return rc;
    }

    points->data[points->size++] = new_el;

    return SUCCESS;
}

return_codes_t points_pop(points_t *points, size_t ind)
{
    if (points->size == 0)
        return ERROR_ARR_EMPTY;

    if (ind >= points->size)
        return ERROR_INVALID_INDEX;

    point_free(&points->data[ind]);

    for (size_t i = ind + 1; i < points->size; i++)
        points->data[i - 1] = points->data[i];

    points->size--;

    return SUCCESS;
}

return_codes_t points_clear(points_t *points)
{
    if (points->size == 0)
        return ERROR_ARR_EMPTY;

    for (size_t i = 0; i < points->size; i++)
        point_free(&points->data[i]);

    points->size = 0;

    return SUCCESS;
}
