#include "point.h"

void point_set_default(point_t &point)
{
    point.x = 0.0;
    point.y = 0.0;
    point.z = 0.0;
}

void point_move(point_t &point, move_data_t &coeff)
{
    point.x += coeff.dx;
    point.y += coeff.dy;
    point.z += coeff.dz;
}

static double to_rad(double &angle)
{
    return (M_PI / 180) * angle;
}

static void rotate_x(point_t &point, point_t &rotate_center, double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));

    double y = point.y;

    point.y = rotate_center.y + (point.y - rotate_center.y) * r_cos + (point.z - rotate_center.z) * r_sin;
    point.z = rotate_center.z - (y - rotate_center.y) * r_sin + (point.z - rotate_center.z) * r_cos;
}

static void rotate_y(point_t &point, point_t &rotate_center, double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double x = point.x;

    point.x = rotate_center.x + (point.x - rotate_center.x) * r_cos - (point.z - rotate_center.z) * r_sin;
    point.z = rotate_center.z + (x - rotate_center.x) * r_sin + (point.z - rotate_center.z) * r_cos;
}

static void rotate_z(point_t &point, point_t &rotate_center, double angle)
{
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));
    double x = point.x;

    point.x = rotate_center.x + (point.x - rotate_center.x) * r_cos + (point.y - rotate_center.y)* r_sin;
    point.y = rotate_center.y -(x - rotate_center.x) * r_sin + (point.y - rotate_center.y) * r_cos;
}

void point_rotate(point_t &point, point_t &rotate_center, rotate_data_t &coeff)
{
    rotate_x(point, rotate_center, coeff.angle_x);
    rotate_y(point, rotate_center, coeff.angle_y);
    rotate_z(point, rotate_center, coeff.angle_z);
}

void point_scale(point_t &point, point_t &scale_center, scale_data_t &coeff)
{
    point.x = point.x * coeff.kx + scale_center.x * (1 - coeff.kx);
    point.y = point.y * coeff.ky + scale_center.y * (1 - coeff.ky);
    point.z = point.z * coeff.kz + scale_center.z * (1 - coeff.kz);
}

return_codes_t point_fread(point_t &point, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;
    else if(fscanf(in, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        return ERROR_FILE_READ;

    return SUCCESS;
}

return_codes_t point_fwrite(point_t &point, FILE *out)
{
    if (fprintf(out, "%lf %lf %lf\n", point.x, point.y, point.z) < 0)
        return ERROR_FILE_WRITE;

    return SUCCESS;
}
