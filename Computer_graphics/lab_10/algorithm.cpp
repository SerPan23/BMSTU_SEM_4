#include "algorithm.h"

#include <cmath>

double to_rad(double teta_grad)
{
    // int tmp = (teta_grad / 360);
    // if (tmp)
    //     teta_grad -= (tmp - 1) * 360;
    return teta_grad * M_PI / 180;
}

void rotateX(double& x, double& y, double& z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double buf = y;
    y = cos(teta) * y - sin(teta) * z;
    z = cos(teta) * z + sin(teta) * buf;
}

void rotateY(double& x, double& y, double& z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double  buf = x;
    x = cos(teta) * x + sin(teta) * z;
    z = cos(teta) * z - sin(teta) * buf;
}

void rotateZ(double& x, double& y, double& z, int teta_grad)
{
    double teta = to_rad(teta_grad);
    double buf = x;
    x = cos(teta) * x - sin(teta) * y;
    y = cos(teta) * y + sin(teta) * buf;
}

Point3d transform(std::shared_ptr<TransformData> transformData, double x, double y, double z, int w, int h)
{
    double x_tmp = x;
    double y_tmp = y;
    double z_tmp = z;

    rotateX(x_tmp, y_tmp, z_tmp, transformData->x_angle);

    rotateY(x_tmp, y_tmp, z_tmp, transformData->y_angle);

    rotateZ(x_tmp, y_tmp, z_tmp, transformData->z_angle);

    x = x_tmp * transformData->scale_coef + w / 2;
    y = y_tmp * transformData->scale_coef + h / 2;
    // x = x * transformData.scale_coef;
    // y = y * transformData.scale_coef;
    return {round(x), round(y), round(z)};
}

void horizon(std::shared_ptr<Drawer> drawer, QColor color, int x1, int y1, int x2, int y2, horizontData& minh, horizontData& maxh, int w, int h)
{
    if (x2 < 0 || x2 > w - 1)
        return;
    if (x1 < 0 || x1 > w - 1)
        return;

    if (x2 < x1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (x2 - x1 == 0) // вертикальный
    {
        maxh[x2] = std::max(maxh[x2], y2);
        minh[x2] = std::min(minh[x2], y2);

        if (x2 >= 0 && x2 < w)
        {
            drawer->draw_line(x1, y1, x2, y2, color);
        }
    }
    else
    {
        int x_pred = x1;
        int y_pred = y1;

        double m = (y2 - y1) / (double)(x2 - x1);
        for (int x = x1; x <= x2; x++)
        {
            int y = (int)(round(m * (x - x1) + y1));
            maxh[x] = std::max(maxh[x], y);
            minh[x] = std::min(minh[x], y);

            if (x >= 0 && x < w)
            {
                drawer->draw_line(x_pred, y_pred, x, y, color);
            }
        }
    }
}

int is_visible(int x, int y, horizontData& minh, horizontData& maxh, int w)
{
    if (y < maxh[x] && y > minh[x]) return 0;
    if (y >= maxh[x]) return 1;
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
Point intersection(int x1, int y1, int x2, int y2, horizontData& horizon, int w)
{
    int xi = x1;
    int yi = y1;
    int delta_x = x2 - x1;
    int delta_y_c = y2 - y1;
    int delta_y_p = horizon[x2] - horizon[x1];
    double m = delta_y_c / (double)(delta_x);

    if (delta_x == 0)
    {
        xi = x2;
        yi = horizon[x2];
    }
    else if (y1 == horizon[x1] && y2 == horizon[x2])
    {
        xi = x1;
        yi = y1;
    }
    else
    {
        xi = x1 - (int)(round(delta_x * (y1 - horizon[x1]) / (double)(delta_y_c - delta_y_p)));
        yi = (int)(round((xi - x1) * m + y1));
    }

    return {xi, yi};
}

void process_edge(std::shared_ptr<Drawer> drawer, QColor color, double x, double y, double& xEdge, double& yEdge, horizontData& minh, horizontData& maxh, int w, int h)
{
    if (xEdge != -1) // Если не первая кривая
        horizon(drawer, color, (int)xEdge, (int)yEdge, (int)x, (int)y, minh, maxh, w, h);
    xEdge = x;
    yEdge = y;
}

void draw_surface(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData)
{
    double x_left = -1;
    double y_left = -1;
    double x_right = -1;
    double y_right = -1;

    double x_pred = 0, y_pred = 0;

    horizontData min_horizon(drawer->width(), drawer->height());
    horizontData max_horizon(drawer->width(), 0);

    for(double z = surface.z_end; z >= surface.z_start; z -= surface.z_step)
    {
        double y_p = surface.func(surface.x_start, z);

        Point3d trans = transform(transformData, surface.x_start, y_p, z, drawer->width(), drawer->height());
        x_pred = trans.x; y_pred = trans.y;

        process_edge(drawer, surface.color, (int)x_pred, (int)y_pred, x_left, y_left, min_horizon, max_horizon, drawer->width(), drawer->height());

        int Pflag = is_visible(x_pred, y_pred, min_horizon, max_horizon, drawer->width());

        for(double x = surface.x_start; x < surface.x_end; x += surface.x_step)
        {
            int x_curr = 0, y_curr = 0;

            Point inter;

            y_p = surface.func(x, z);

            Point3d trans = transform(transformData, x, y_p, z, drawer->width(), drawer->height());
            x_curr = trans.x; y_curr = trans.y;

            int Tflag = is_visible(x_curr, y_curr, min_horizon, max_horizon, drawer->width());
            if (Tflag == Pflag)
            {
                if (Tflag != 0)
                {
                    horizon(drawer, surface.color, x_pred, y_pred, x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                }
            }
            else if (Tflag == 0)
            {
                if (Pflag == 1)
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, max_horizon, drawer->width());
                }
                else
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, min_horizon, drawer->width());
                }
                horizon(drawer, surface.color, x_pred, y_pred, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());
            }
            else if (Tflag == 1)
            {
                if (Pflag == 0)
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, max_horizon, drawer->width());
                    horizon(drawer, surface.color, x_pred, y_pred, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());
                }
                else
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, max_horizon, drawer->width());
                    horizon(drawer, surface.color, x_pred, y_pred, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());

                    inter = intersection(x_pred, y_pred, x_curr, y_curr, min_horizon, drawer->width());
                    horizon(drawer, surface.color, inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                }
            }
            else
            {
                if (Pflag == 0)
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, min_horizon, drawer->width());
                    horizon(drawer, surface.color, x_pred, y_pred, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());
                }
                else
                {
                    inter = intersection(x_pred, y_pred, x_curr, y_curr, max_horizon, drawer->width());
                    horizon(drawer, surface.color, x_pred, y_pred, inter.x(), inter.y(), min_horizon, max_horizon, drawer->width(), drawer->height());

                    inter = intersection(x_pred, y_pred, x_curr, y_curr, min_horizon, drawer->width());
                    horizon(drawer, surface.color, inter.x(), inter.y(), x_curr, y_curr, min_horizon, max_horizon, drawer->width(), drawer->height());
                }
            }
            Pflag = Tflag;
            x_pred = x_curr;
            y_pred = y_curr;
        }
        process_edge(drawer, surface.color, (int)x_pred, (int)y_pred, x_right, y_right, min_horizon, max_horizon, drawer->width(), drawer->height());
    }
}
