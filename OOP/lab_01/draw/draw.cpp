#include "draw.h"

struct line
{
    point_t first_point;
    point_t second_point;
};
using line_t = struct line;


static point_t point_transform_to_screen(point_t point, const draw_view_t &view)
{
    point.x += view.width / 2;
    point.y += view.height / 2;

    return point;
}

static line_t get_line(draw_view_t &view, const edge_t &edge, const points_t &points)
{
    line_t line;

    line.first_point = point_transform_to_screen(points.data[edge.first_point_index], view);
    line.second_point = point_transform_to_screen(points.data[edge.second_point_index], view);

    return line;
}

static return_codes_t draw_line(draw_view_t &view, const line_t &line)
{
    if (!view.scene)
        return ERROR_WRONG_SCENE;

    view.scene->addLine(line.first_point.x, line.first_point.y,
                        line.second_point.x, line.second_point.y);
    return SUCCESS;
}

static return_codes_t draw_lines(const points_t &points, const edges_t &edges, draw_view_t &view)
{
    if (points.data == NULL || edges.data == NULL)
        return ERROR_MEM_ALLOC;

    if (!view.scene)
        return ERROR_WRONG_SCENE;

    return_codes rc = SUCCESS;

    line_t line;

    for (int i = 0; rc == SUCCESS && i < edges.size; i++)
    {
        line = get_line(view, edges.data[i], points);
        rc = draw_line(view, line);
    }

    return rc;
}

return_codes draw_figure(const figure_t &figure, draw_view_t &view)
{
    return_codes rc = scene_clear(view);

    if (rc == SUCCESS)
        rc = draw_lines(figure.points, figure.edges, view);

    return rc;
}

return_codes scene_clear(draw_view_t &view)
{
    if (!view.scene)
        return ERROR_WRONG_SCENE;

    view.scene->clear();

    return SUCCESS;
}
