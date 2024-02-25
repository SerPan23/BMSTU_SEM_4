#include "line.h"

#define EPS 1e-8

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

point_t *get_lines_cross(line_t *a, line_t *b)
{
    double x, y;

    double k1 = (a->end->y - a->start->y) / (a->end->x - a->start->x);
    double k2 = (b->end->y - b->start->y) / (b->end->x - b->start->x);

    if (a->start->x == a->end->x)
    {
        x = a->start->x;
        y = k2 * x + b->start->y - k2 * b->start->x;
    }
    else if (b->start->x == b->end->x)
    {
        x = b->start->x;
        y = k1 * x + a->start->y - k1 * a->start->x;
    }
    else
    {
        // first line

        double b1 = a->start->y - a->start->x * k1;

        // second line

        double b2 = b->start->y - b->start->x * k2;


        x = (b2 - b1) / (k1 - k2);
        y = k1 * x + b1;
    }

    return point_create(x, y);
}

void get_min_max_point(line_t *a, point_t *pmin, point_t *pmax)
{
    pmin->x = std::fmin(pmin->x, std::fmin(a->start->x, a->end->x));
    pmin->y = std::fmin(pmin->y, std::fmin(a->start->y, a->end->y));

    pmax->x = std::fmax(pmax->x, std::fmax(a->start->x, a->end->x));
    pmax->y = std::fmax(pmax->y, std::fmax(a->start->y, a->end->y));
}
