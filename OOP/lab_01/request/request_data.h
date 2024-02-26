#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

struct move_data
{
    double dx;
    double dy;
    double dz;
};

using move_data_t = struct move_data;

struct rotate_data
{
    double angle_x;
    double angle_y;
    double angle_z;
};

using rotate_data_t = struct rotate_data;

struct scale_data
{
    double kx;
    double ky;
    double kz;
};

using scale_data_t = struct scale_data;

#endif // REQUEST_DATA_H
