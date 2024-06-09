#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "drawer.h"
#include "funcs.h"

struct TransformData
{
    int x_angle = 0;
    int y_angle = 0;
    int z_angle = 0;

    int scale_coef = 1;

    void x_rotate(int angle)
    {
        x_angle += angle;
    }

    void y_rotate(int angle)
    {
        y_angle += angle;
    }

    void z_rotate(int angle)
    {
        z_angle += angle;
    }

    void set_scale(int scale)
    {
        scale_coef = scale;
    }
};

struct SurfaceData
{
    double x_start, x_end, x_step;
    double z_start, z_end, z_step;
    Funcs::func_ptr func;
    QColor color;
};

struct Point3d
{
    double x, y, z;
};

void draw_surface(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData);

#endif // ALGORITHM_H
