#include "shapes.h"

int shapes_alloc(shapes_t *shapes, size_t size)
{
    shape_t **tmp = (shape_t **) malloc(size * sizeof(shape_t*));
    if (tmp == NULL)
        return ERROR_MEM_ALLOC;

    shapes->data = tmp;
    shapes->size = 0;
    shapes->size_alloced = size;

    return EXIT_SUCCESS;
}

void shapes_free(shapes_t *shapes)
{
    for (size_t i = 0; i < shapes->size_alloced; i++)
        shape_free(&shapes->data[i]);

    free(shapes->data);

    shapes->data = NULL;
    shapes->size = 0;
    shapes->size_alloced = 0;
}

int shapes_realloc(shapes_t *shapes, size_t new_size)
{
    shape_t **tmp = (shape_t **) realloc(shapes->data, new_size * sizeof(shape_t *));
    if (tmp == NULL)
        return ERROR_MEM_ALLOC;

    shapes->data = tmp;
    shapes->size_alloced = new_size;

    return EXIT_SUCCESS;
}

int shapes_push(shapes_t *shapes, shape_t *new_el)
{
    if (shapes->size + 1 > shapes->size_alloced)
    {
        int rc =  shapes_realloc(shapes, shapes->size_alloced + 1 + shapes->size_alloced * 0.1);

        if (rc != EXIT_SUCCESS)
            return rc;
    }

    shapes->data[shapes->size++] = new_el;
    return EXIT_SUCCESS;
}

int shapes_pop(shapes_t *shapes, size_t ind)
{
    if (shapes->size == 0)
        return ERROR_ARR_EMPTY;

    if (ind >= shapes->size)
        return ERROR_INVALID_INDEX;

    shape_free(&shapes->data[ind]);

    for (size_t i = ind + 1; i < shapes->size; i++)
        shapes->data[i - 1] = shapes->data[i];

    shapes->size--;
    return EXIT_SUCCESS;
}

int shapes_clear(shapes_t *shapes)
{
    if (shapes->size == 0)
        return ERROR_ARR_EMPTY;

    for (size_t i = 0; i < shapes->size; i++)
        shape_free(&shapes->data[i]);

    shapes->size = 0;
    return EXIT_SUCCESS;
}

shapes_t shapes_move(shapes_t *figure, point_t *offset)
{
    shapes_t new_figure;
    shapes_alloc(&new_figure, figure->size);

    for (size_t i = 0; i < figure->size; i++)
        shapes_push(&new_figure, shape_move(figure->data[i], offset));

    return new_figure;
}

shapes_t shapes_rotate(shapes_t *figure, point_t *rotate_center, double angel)
{
    shapes_t new_figure;
    shapes_alloc(&new_figure, figure->size);

    for (size_t i = 0; i < figure->size; i++)
        shapes_push(&new_figure, shape_rotate(figure->data[i], rotate_center, angel));

    return new_figure;
}

shapes_t shapes_scale(shapes_t *figure, point_t *scale_center, point_t *scale)
{
    shapes_t new_figure;
    shapes_alloc(&new_figure, figure->size);

    for (size_t i = 0; i < figure->size; i++)
        shapes_push(&new_figure, shape_scale(figure->data[i], scale_center, scale));

    return new_figure;
}
