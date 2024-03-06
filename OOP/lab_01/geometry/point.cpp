#include "point.h"

point_t point_set_default()
{
    return point_t{0.0, 0.0, 0.0};
}

return_codes_t point_move(point_t &point, const move_data_t &coeff)
{
    point.x += coeff.dx;
    point.y += coeff.dy;
    point.z += coeff.dz;

    return SUCCESS;
}

static double to_rad(const double &angle)
{
    return (M_PI / 180) * angle;
}

static return_codes_t rotate_x(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_y = point.y;

    point.y = point.y * r_cos + point.z * r_sin;
    point.z = point.z * r_cos - tmp_y * r_sin;

    return SUCCESS;
}

static return_codes_t rotate_y(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_x = point.x;

    point.x = point.x * r_cos - point.z * r_sin;
    point.z = point.z  * r_cos + tmp_x * r_sin;

    return SUCCESS;
}

static return_codes_t rotate_z(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_x = point.x;

    point.x = point.x * r_cos + point.y * r_sin;
    point.y = point.y * r_cos - tmp_x * r_sin;

    return SUCCESS;
}

static return_codes_t move_to_local_center(point_t &point, const point_t &rotate_center)
{
    point_t point_neg = point_to_negative(rotate_center);
    move_data_t move_data = point_to_move_data(point_neg);
    return point_move(point, move_data);
}

static return_codes_t move_to_global_center(point_t &point, const point_t &rotate_center)
{
    move_data_t move_data = point_to_move_data(rotate_center);
    return point_move(point, move_data);
}

static return_codes_t rotate(point_t &point, const rotate_data_t &coeff)
{
    return_codes_t rc = rotate_x(point, coeff.angle_x);

    if (rc == SUCCESS)
    {
        rc = rotate_y(point, coeff.angle_y);

        if (rc == SUCCESS)
            rc = rotate_z(point, coeff.angle_z);
    }

    return rc;
}

return_codes_t point_rotate(point_t &point, const point_t &rotate_center, const rotate_data_t &coeff)
{
    return_codes_t rc = move_to_local_center(point, rotate_center);

    if (rc == SUCCESS)
    {
        rc = rotate(point, coeff);

        if (rc == SUCCESS)
            rc = move_to_global_center(point, rotate_center);
    }

    return rc;
}

return_codes_t point_scale(point_t &point, const point_t &scale_center, const scale_data_t &coeff)
{
    point.x = (point.x - scale_center.x) * coeff.kx + scale_center.x;
    point.y = (point.y - scale_center.y) * coeff.ky + scale_center.y;
    point.z = (point.z - scale_center.z) * coeff.kz + scale_center.z;

    return SUCCESS;
}

return_codes_t point_fread(point_t &point, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    if(fscanf(in, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        return ERROR_FILE_READ;

    return SUCCESS;
}

return_codes_t point_fwrite(const point_t &point, FILE *out)
{
    if (out == NULL)
        return ERROR_FILE_OPEN;

    if (fprintf(out, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        return ERROR_FILE_WRITE;

    return SUCCESS;
}

move_data_t point_to_move_data(const point_t &point)
{
    return move_data_t{point.x, point.y, point.z};
}

point_t point_to_negative(const point_t &point)
{
    return point_t{-point.x, -point.y, -point.z};
}
