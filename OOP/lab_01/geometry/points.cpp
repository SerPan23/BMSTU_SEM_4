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
    points_set_default(points);
}

void points_set_default(points_t &points)
{
    points.data = NULL;
    points.size = 0;
}

return_codes_t points_move_all(points_t &points, move_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    for (int i = 0; i < points.size; i++)
        point_move(points.data[i], coeff);

    return SUCCESS;
}

return_codes_t points_rotate_all(points_t &points, point_t &rotate_center, rotate_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    for (int i = 0; i < points.size; i++)
        point_rotate(points.data[i], rotate_center, coeff);

    return SUCCESS;
}

return_codes_t points_scale_all(points_t &points, point_t &scale_center, scale_data_t &coeff)
{
    if (!points.data)
        return ERROR_FIGURE_NOT_LOADED;

    for (int i = 0; i < points.size; i++)
        point_scale(points.data[i], scale_center, coeff);

    return SUCCESS;
}

return_codes_t points_fread(points_t &points, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    return_codes_t rc = points_count_fread(points, in);
    if (!rc)
    {
        rc = points_alloc(points);
        if (!rc)
        {
            rc = points_data_fread(points, in);
            if (rc)
                points_free(points);
        }
    }

    return rc;
}

return_codes_t points_count_fread(points_t &points, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;
    else if (fscanf(in, "%d", &points.size) != 1)
        return ERROR_FILE_READ;
    else if (points.size <= 0)
        return ERROR_POINTS_SIZE;

    return SUCCESS;
}

return_codes_t points_data_fread(points_t &points, FILE *in)
{
    return_codes_t rc = SUCCESS;
    if (in == NULL)
        rc = ERROR_FILE_OPEN;
    else if (points.size <= 0)
        rc = ERROR_POINTS_SIZE;
    else if (!points.data)
        rc = ERROR_MEM_ALLOC;
    else
        for (int i = 0; rc == SUCCESS && i < points.size; i++)
            rc = point_fread(points.data[i], in);

    return rc;
}

return_codes_t points_fwrite(points_t &points, FILE *out)
{
    return_codes_t rc = SUCCESS;
    if (!points.data)
        rc = ERROR_EMPTY_DATA;
    else if (fprintf(out, "%d\n", points.size) < 0)
        rc = ERROR_FILE_WRITE;
    else
        for (int i = 0; rc == SUCCESS && i < points.size; i++)
            rc = point_fwrite(points.data[i], out);
    return rc;
}
