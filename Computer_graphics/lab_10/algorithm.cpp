#include "algorithm.h"

#include <cmath>

double to_rad(double teta_grad)
{
    // int tmp = (teta_grad / 360);
    // if (tmp)
    //     teta_grad -= (tmp - 1) * 360;
    return teta_grad * M_PI / 180;
}

Point3d rotateX(double x, double y, double z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double buf = y;
    y = cos(teta) * y - sin(teta) * z;
    z = cos(teta) * z + sin(teta) * buf;
    return {x, y, z};
}

Point3d rotateY(double x, double y, double z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double  buf = x;
    x = cos(teta) * x - sin(teta) * z;
    z = cos(teta) * z + sin(teta) * buf;
    return {x, y, z};
}

Point3d rotateZ(double x, double y, double z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double buf = x;
    x = cos(teta) * x - sin(teta) * y;
    y = cos(teta) * y + sin(teta) * buf;
    return {x, y, z};
}

Point3d trans_point(std::shared_ptr<TransformData> transformData, double x, double y, double z, int w, int h)
{
    Point3d p;

    p = rotateX(x, y, z, transformData->x_angle);
    x = p.x;
    y = p.y;
    z = p.z;

    p = rotateY(x, y, z, transformData->y_angle);
    x = p.x;
    y = p.y;
    z = p.z;

    p = rotateZ(x, y, z, transformData->z_angle);
    x = p.x;
    y = p.y;
    z = p.z;

    x = x * transformData->scale_coef + w / 2;
    y = y * transformData->scale_coef + h / 2;
    // x = x * transformData.scale_coef;
    // y = y * transformData.scale_coef;
    return {x, y, z};
}

bool is_visible(std::shared_ptr<Drawer> drawer, Point& point)
{
    return (0 <= point.x() < drawer->width()) and (0 <= point.y() < drawer->height());
}

bool draw_point(std::shared_ptr<Drawer> drawer, int x, double y,
                horizontData& hh, horizontData& lh, QColor color)
{
    Point p(x, int(round(y)));

    if (!is_visible(drawer, p))
        return false;

    if (y > hh[x])
        hh[x] = y;

    else if (y < lh[x])
        lh[x] = y;

    drawer->draw_point(p, color);

    return true;
}

void draw_horizon_part(std::shared_ptr<Drawer> drawer, Point& p1, Point& p2,
                       horizontData& hh, horizontData& lh, QColor color)
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    double l = dx ? dx > dy : dy;
    dx /= l;
    dy /= l;

    double x = p1.x(), y = p1.y();

    for (int i = 0; i < int(l) + 1; i++)
    {
        if (!draw_point(drawer, int(round(x)), y, hh, lh, color))
            return;
        x += dx;
        y += dy;
    }
}

void draw_horizon(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData,
                  horizontData& high_horizon, horizontData& low_horizon, double z)
{
    Point prev;
    bool is_first = true;
    for (double x = surface.x_start; x <= surface.x_end; x += surface.x_step)
    {
        Point3d tmp = trans_point(transformData, x, surface.func(x, z), z,
                                  drawer->width(), drawer->height());
        Point current(tmp.x, tmp.y);

        if (is_first)
        {
            is_first = false;
        }
        else
        {
            draw_horizon_part(drawer, prev, current, high_horizon, low_horizon, surface.color);
        }
        prev = current;
    }
}

void draw_surface(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData)
{
    std::vector<double> high_horizon(drawer->width(), 0);
    std::vector<double> low_horizon(drawer->width(), drawer->height());

    for (double z = surface.z_end; z >= surface.z_start; z -= surface.z_step)
        draw_horizon(drawer, surface, transformData, high_horizon, low_horizon, z);

    for (double z = surface.z_end; z >= surface.z_start; z -= surface.z_step)
    {
        Point3d p1_3d = trans_point(transformData, surface.x_start,
                                 surface.func(surface.x_start, z), z, drawer->width(), drawer->height());
        Point p1(p1_3d.x, p1_3d.y);

        Point3d p2_3d = trans_point(transformData, surface.x_start,
                                 surface.func(surface.x_start, z + surface.z_step), z  + surface.z_step,
                                 drawer->width(), drawer->height());
        Point p2(p2_3d.x, p2_3d.y);

        drawer->draw_line(p1, p2, surface.color);


        p1_3d = trans_point(transformData, surface.x_end,
                                 surface.func(surface.x_end, z), z, drawer->width(), drawer->height());
        p1 = Point(p1_3d.x, p1_3d.y);

        p2_3d = trans_point(transformData, surface.x_end,
                            surface.func(surface.x_end, z + surface.z_step), z  + surface.z_step,
                            drawer->width(), drawer->height());
        p2 = Point(p2_3d.x, p2_3d.y);
        drawer->draw_line(p1, p2, surface.color);
    }

}
