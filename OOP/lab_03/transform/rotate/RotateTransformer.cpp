#include "RotateTransformer.h"

RotateTransformer::RotateTransformer(const double x, const double y, const double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

Matrix4 RotateTransformer::transform(const Matrix4& mat)
{
    Matrix4 model(mat);
    model = rotate(model, radians(x_), Vector3(1.0, 0.0, 0.0));
    model = rotate(model, radians(y_), Vector3(0.0, 1.0, 0.0));
    model = rotate(model, radians(z_), Vector3(0.0, 0.0, -1.0));

    return Matrix4(model);
}
