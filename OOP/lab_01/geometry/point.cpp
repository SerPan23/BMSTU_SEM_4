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

static void rotate_x(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_y = point.y;

    point.y = point.y * r_cos + point.z * r_sin;
    point.z = point.z * r_cos - tmp_y * r_sin;
}

static void rotate_y(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_x = point.x;

    point.x = point.x * r_cos - point.z * r_sin;
    point.z = point.z  * r_cos + tmp_x * r_sin;
}

static void rotate_z(point_t &point, const double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double tmp_x = point.x;

    point.x = point.x * r_cos + point.y  * r_sin;
    point.y = point.y * r_cos - tmp_x * r_sin;
}

static return_codes_t rotate_transofrm(point_t &point, const point_t &rotate_center, const rotate_data_t &coeff)
{
    point.x -= rotate_center.x;
    point.y -= rotate_center.y;
    point.z -= rotate_center.z;

    rotate_x(point, coeff.angle_x);
    rotate_y(point, coeff.angle_y);
    rotate_z(point, coeff.angle_z);

    point.x += rotate_center.x;
    point.y += rotate_center.y;
    point.z += rotate_center.z;

    return SUCCESS;
}

return_codes_t point_rotate(point_t &point, const point_t &rotate_center, const rotate_data_t &coeff)
{
    return rotate_transofrm(point, rotate_center, coeff);
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
