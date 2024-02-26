#include "draw.h"

point_t point_transform_to_screen(point_t point, draw_view_t &view)
{
    point.x += view.width / 2;
    point.y += view.height / 2;

    return point;
}

line_t get_line(draw_view_t &view, edge_t &edge, point_t *array_points)
{
    line_t line;

    line.first_point = point_transform_to_screen(array_points[edge.first_point_index], view);
    line.second_point = point_transform_to_screen(array_points[edge.second_point_index], view);

    return line;
}

return_codes draw_line(draw_view_t &view, line_t &line)
{
    if (!view.scene)
        return ERROR_WRONG_SCENE;

    view.scene->addLine(line.first_point.x, line.first_point.y,
                        line.second_point.x, line.second_point.y);
    return SUCCESS;
}

return_codes draw_lines(draw_view_t &view, points_t &points, edges_t &edges)
{
    if (points.data == NULL || edges.data == NULL)
        return ERROR_MEM_ALLOC;

    if (!view.scene)
        return ERROR_WRONG_SCENE;

    return_codes rc = SUCCESS;

    line_t line;
    for (int i = 0; rc == SUCCESS && i < edges.size; i++)
    {
        line = get_line(view, edges.data[i], points.data);
        rc = draw_line(view, line);
    }

    return rc;
}

return_codes draw_figure(figure_t &figure, draw_view_t &view)
{
    return_codes rc = scene_clear(view);

    if (!rc)
        rc = draw_lines(view, figure.points, figure.edges);

    return rc;
}

return_codes scene_clear(draw_view_t &view)
{
    if (!view.scene)
        return ERROR_WRONG_SCENE;

    view.scene->clear();
    return SUCCESS;
}
