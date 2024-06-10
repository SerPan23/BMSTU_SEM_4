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

Point3d transform(std::shared_ptr<TransformData> transformData, double x, double y, double z, int w, int h)
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
    return {round(x), round(y), round(z)};
}

void horizon(double start_x, double start_y, double end_x, double end_y, horizontData minh, horizontData maxh, int w, int h)
{
    if (end_x == start_x)
    {
        if (end_x >= w)
            return;
        maxh[end_x] = std::max(maxh[end_x], end_y);
        minh[end_x] = std::min(minh[end_x], end_y);
    }
    else
    {
        double k = (end_y - start_y) / (end_x - start_x);
        for (int x = start_x; x < end_x + 1; x++)
        {
            if (x >= w)
                break;

            double y = k * (x - start_x) + start_y;
            maxh[x] = std::max(maxh[x], y);
            minh[x] = std::min(minh[x], y);
        }
    }
}

int is_visible(double x, double y, horizontData minh, horizontData maxh, int w)
{
    int x_ = int(round(x));

    if (x_ < 0 or x_ >= w)
        return 0;

    if (y < maxh[x_] and y > minh[x_])
        return 0;

    if (y >= maxh[x_])
        return 1;

    return -1;
}

int sign(double a)
{
    if (a < 0)
        return -1;
    if (a > 0)
        return 1;
    return 0;
}
Point intersection(int x_start, int y_start, int x_end, int y_end, horizontData horizon, int w)
{
    if (x_end == x_start)
    {
        if (0 <= x_end < w)
            return {x_end, static_cast<int>(horizon[x_end])};
        return {w - 1, static_cast<int>(horizon[w - 1])};
    }

    double k = (y_end - y_start) * 1.0 / (x_end - x_start);
    int sy = sign(y_start + k - horizon[x_start + 1]);
    int sc = sy;
    double y = y_start + k;
    double x = x_start + 1;
    while (sc == sy and x < x_end and x < w)
    {
        sc = sign(y - horizon[x]);
        y += k;
        x += 1;
    }

    return {int(round(x)), int(round(y))};
}

void draw_surface(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData)
{
    double z = surface.z_end;
    double iz = 0;
    bool visible = true;
    int x_left = -1;
    int y_left = -1;
    int x_right = -1;
    int y_right = -1;

    horizontData max_horizon(drawer->width(), 0);
    horizontData min_horizon(drawer->width(), drawer->height());

    while (z >= surface.z_start)
    {
        double x_last = surface.x_start;
        double y_last = surface.func(surface.x_start, z);
        double z_buf = z;
        Point3d trans = transform(transformData, x_last, y_last, z, drawer->width(), drawer->height());
        x_last = trans.x; y_last = trans.y; z_buf = trans.z;

        if (x_left != -1)
        {
            if (is_visible(x_left, y_left, min_horizon, max_horizon, drawer->width()) and
                is_visible(x_last, y_last, min_horizon, max_horizon, drawer->width()))
            {
                drawer->draw_line(x_last, y_last, x_left, y_left, surface.color);
            }
            horizon(x_last, y_last, x_left, y_left, min_horizon, max_horizon, drawer->width(), drawer->height());
        }

        x_left = x_last;
        y_left = y_last;

        int prev_visibility = is_visible(x_last, y_last, min_horizon, max_horizon, drawer->width());
        double x = surface.x_start;

        double x_curr, y_curr;
        while(x < surface.x_end)
        {
            double y = surface.func(x, z);
            Point3d trans = transform(transformData, x, y, z, drawer->width(), drawer->height());
            x_curr = trans.x; y_curr = trans.y; z_buf = trans.z;

            int curr_visibility = is_visible(x_curr, y_curr, min_horizon, max_horizon, drawer->width());
            if (prev_visibility == curr_visibility)
            {
                if (curr_visibility)
                {
                    drawer->draw_line(x_last, y_last, x_curr, y_curr, surface.color);
                    horizon(x_last, y_last, x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                }
            }
            else
            {
                Point inter;
                if (!curr_visibility && (x_curr - x_last) > 1)
                {

                    if (prev_visibility == 1)
                        inter = intersection(x_last, y_last, x_curr, y_curr, max_horizon, drawer->width());
                    else
                        inter = intersection(x_last, y_last, x_curr, y_curr, min_horizon, drawer->width());

                    drawer->draw_line(x_last, y_last, inter.x(), inter.y(), surface.color);
                    horizon(x_last, y_last, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());
                }
                else if (curr_visibility == 1)
                {
                    if (!prev_visibility)
                    {
                        inter = intersection(x_last, y_last, x_curr, y_curr, max_horizon, drawer->width());

                        drawer->draw_line(inter.x(), inter.y(), x_curr, y_curr, surface.color);
                        horizon(inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                    }
                    else
                    {
                        inter = intersection(x_last, y_last, x_curr, y_curr, min_horizon, drawer->width());

                        drawer->draw_line(x_last, y_last, inter.x(), inter.y(), surface.color);
                        horizon(x_last, y_last, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());

                        inter = intersection(x_last, y_last, x_curr, y_curr, max_horizon, drawer->width());
                        drawer->draw_line(inter.x(), inter.y(), x_curr, y_curr, surface.color);
                        horizon(inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                    }
                }
                else
                {
                    if (!prev_visibility)
                    {
                        inter = intersection(x_last, y_last, x_curr, y_curr, min_horizon, drawer->width());

                        drawer->draw_line(inter.x(), inter.y(), x_curr, y_curr, surface.color);
                        horizon(inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                    }
                    else
                    {
                        inter = intersection(x_last, y_last, x_curr, y_curr, max_horizon, drawer->width());

                        drawer->draw_line(x_last, y_last, inter.x(), inter.y(), surface.color);
                        horizon(x_last, y_last, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());

                        inter = intersection(x_last, y_last, x_curr, y_curr, min_horizon, drawer->width());
                        drawer->draw_line(inter.x(), inter.y(), x_curr, y_curr, surface.color);
                        horizon(inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                    }
                }
            }
            prev_visibility = curr_visibility;
            x_last = x_curr;
            y_last = y_curr;

            x += surface.x_step;
        }
        if (x_right != -1)
        {
            drawer->draw_line(x_right, y_right, x_curr, y_curr, surface.color);
            horizon(x_right, y_right, x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
        }
        x_right = x_curr;
        y_right = y_curr;
        z -= surface.z_step;
    }
}
