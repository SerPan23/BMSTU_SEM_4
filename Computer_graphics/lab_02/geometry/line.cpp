#include "line.h"

line_t *line_create(point_t *start, point_t *end, int width)
{
    line_t *line = (line_t *) malloc(sizeof(line_t));
    if (line == NULL)
        return NULL;

    line->start = start;
    line->end = end;
    line->width = 1;

    return line;
}

line_t *line_create(point_t *start, point_t *end)
{
    return line_create(start, end, 1);
}

void line_free(line_t **line)
{
    if (*line)
    {
        point_free(&(*line)->start);
        point_free(&(*line)->end);
        free(*line);
    }

    *line = NULL;
}

line_t *line_move(line_t *line, point_t *offset)
{
    return line_create(
        point_move(line->start, offset),
        point_move(line->end, offset));
}

line_t *line_rotate(line_t *line, point_t *rotate_center, double angel)
{
    return line_create(
        point_rotate(line->start, rotate_center, angel),
        point_rotate(line->end, rotate_center, angel));
}

line_t *line_scale(line_t *line, point_t *scale_center, point_t *scale)
{
    return line_create(
        point_scale(line->start, scale_center, scale),
        point_scale(line->end, scale_center, scale));
}
