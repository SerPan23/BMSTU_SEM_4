#include "points.h"

return_codes_t points_alloc(points_t &points)
{
    if (points.size <= 0)
        return ERROR_POINTS_SIZE;

    point_t *tmp = (point_t *) malloc(points.size * sizeof(point_t));

    if (!tmp)
        return ERROR_MEM_ALLOC;

    points.data = tmp;

    return SUCCESS;
}

void points_free(points_t &points)
{
    free(points.data);
    points = points_set_default();
}

points_t points_set_default()
{
    return points_t{NULL, 0};
}

return_codes_t points_move_all(points_t &points, const move_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    return_codes_t rc = SUCCESS;

    for (int i = 0; rc == SUCCESS && i < points.size; i++)
        rc = point_move(points.data[i], coeff);

    return rc;
}

return_codes_t points_rotate_all(points_t &points, const point_t &rotate_center, const rotate_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    return_codes_t rc = SUCCESS;

    for (int i = 0; rc == SUCCESS && i < points.size; i++)
        rc = point_rotate(points.data[i], rotate_center, coeff);

    return SUCCESS;
}

return_codes_t points_scale_all(points_t &points, const point_t &scale_center, const scale_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    return_codes_t rc = SUCCESS;

    for (int i = 0; rc == SUCCESS && i < points.size; i++)
        rc = point_scale(points.data[i], scale_center, coeff);

    return SUCCESS;
}

static return_codes_t points_count_fread(int &count, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    if (fscanf(in, "%d", &count) != 1)
        return ERROR_FILE_READ;

    if (count <= 0)
        return ERROR_POINTS_SIZE;

    return SUCCESS;
}

static return_codes_t points_data_fread(point_t *data, const int &count, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    if (count <= 0)
        return ERROR_POINTS_SIZE;

    if (!data)
        return ERROR_MEM_ALLOC;

    return_codes_t rc = SUCCESS;

    for (int i = 0; rc == SUCCESS && i < count; i++)
        rc = point_fread(data[i], in);

    return rc;
}

return_codes_t points_fread(points_t &points, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    return_codes_t rc = points_count_fread(points.size, in);

    if (rc == SUCCESS)
    {
        rc = points_alloc(points);

        if (rc == SUCCESS)
        {
            rc = points_data_fread(points.data, points.size, in);

            if (rc != SUCCESS)
                points_free(points);
        }
    }

    return rc;
}


return_codes_t points_fwrite(const points_t &points, FILE *out)
{
    if (out == NULL)
        return ERROR_FILE_OPEN;

    if (!points.data)
        return ERROR_EMPTY_DATA;

    if (fprintf(out, "%d\n", points.size) < 0)
        return ERROR_FILE_WRITE;

    return_codes_t rc = SUCCESS;

    for (int i = 0; rc == SUCCESS && i < points.size; i++)
        rc = point_fwrite(points.data[i], out);

    return rc;
}
