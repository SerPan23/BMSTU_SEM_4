#ifndef LINE_H
#define LINE_H

#include "point.h"

struct line
{
    point_t *start;
    point_t *end;
    int width;
};

using line_t = struct line;

line_t *line_create(point_t *start, point_t *end, int width);
line_t *line_create(point_t *start, point_t *end);
void line_free(line_t **line);

line_t *line_move(line_t *line, point_t *offset);
line_t *line_rotate(line_t *line, point_t *rotate_center, double angel);
line_t *line_scale(line_t *line, point_t *scale_center, point_t *scale);

#endif // LINE_H
