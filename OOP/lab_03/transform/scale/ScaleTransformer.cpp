#include "ScaleTransformer.h"

ScaleTransformer::ScaleTransformer(const double x, const double y, const double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}


Matrix4 ScaleTransformer::transform(const Matrix4& mat)
{
    Vector3 scl(x_, y_, z_);

    Matrix4 model(mat);

    return scale(model, scl);;
}
