#include "MoveTransformer.h"

MoveTransformer::MoveTransformer(const double x, const double y, const double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

Matrix4 MoveTransformer::transform(const Matrix4& mat)
{
    Vector3 scl(x_, y_, z_);

    Matrix4 model(mat);

    return translate(model, scl);;
}
