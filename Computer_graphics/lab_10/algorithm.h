#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "drawer.h"
#include "funcs.h"

struct TransformData
{
    int x_angle = 0;
    int y_angle = 0;
    int z_angle = 0;

    double scale_coef = 1;

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

    void set_scale(double scale)
    {
        scale_coef = scale;
    }
};

struct SurfaceData
{
    double x_start = 0, x_end = 0, x_step = 0;
    double z_start = 0, z_end = 0, z_step = 0;
    Funcs::func_ptr func{nullptr};
    QColor color;
};

struct Point3d
{
    double x, y, z;
};

// using horizontData = std::vector<double>;

class horizontData
{
public:

    horizontData(int size, double item)
    {
        data = std::vector<int>(size, item);
    }

    int& operator[](int index)
    {
        if (index < 0)
        {
            // qDebug() << "WROND INDEX (size = " << data.size() << " index = " << index << ")";
            index = 0;
        }
        else if (index >= data.size())
        {
            // qDebug() << "WROND INDEX (size = " << data.size() << " index = " << index << ")";
            index = data.size() - 1;
        }

        return data[index];
    }

private:
    std::vector<int> data;
};

void draw_surface(std::shared_ptr<Drawer> drawer, SurfaceData surface, std::shared_ptr<TransformData> transformData);

#endif // ALGORITHM_H
