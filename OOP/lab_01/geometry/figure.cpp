#include "figure.h"

figure_t &figure_create(void)
{
    static figure_t figure;

    point_set_default(figure.center);

    points_set_default(figure.points);

    edges_set_default(figure.edges);

    return figure;
}

void figure_free(figure_t &figure)
{
    points_free(figure.points);
    edges_free(figure.edges);
}

return_codes_t figure_move(figure_t &figure, move_data_t &coeff)
{
    point_move(figure.center, coeff);
    return points_move_all(figure.points, coeff);
}

return_codes_t figure_rotate(figure_t &figure, rotate_data_t &coeff)
{
    return points_rotate_all(figure.points, figure.center, coeff);
}

return_codes_t figure_scale(figure_t &figure, scale_data_t &coeff)
{   
    return points_scale_all(figure.points, figure.center, coeff);
}

static return_codes_t figure_fread(figure_t &figure, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    figure = figure_create();

    return_codes_t rc = points_fread(figure.points, in);

    if (rc != SUCCESS)
        return rc;

    rc = edges_fread(figure.edges, in);

    if (rc != SUCCESS)
        points_free(figure.points);

    return rc;
}

return_codes_t figure_load(figure_t &figure, char *filename)
{
    if (filename == NULL)
        return ERROR_FILE_OPEN;

    FILE *in = fopen(filename, "r");

    if (in == NULL)
        return ERROR_FILE_OPEN;

    figure_t current_figure;

    return_codes_t rc = figure_fread(current_figure, in);

    fclose(in);

    if (rc == SUCCESS)
    {
        figure_free(figure);
        figure = current_figure;
    }

    return rc;
}

static return_codes_t figure_fwrite(figure_t &figure, FILE *out)
{
    return_codes_t rc = points_fwrite(figure.points, out);

    if (rc == SUCCESS)
        rc = edges_fwrite(figure.edges, out);

    return rc;
}

return_codes_t figure_save(figure_t &figure, char *filename)
{
    if (filename == NULL)
        return ERROR_FILE_OPEN;

    if (!figure.points.data || !figure.edges.data)
        return ERROR_EMPTY_DATA;

    FILE *out = fopen(filename, "w");

    if (out == NULL)
        return ERROR_FILE_WRITE;

    return_codes_t rc = figure_fwrite(figure, out);

    fclose(out);

    return rc;
}
