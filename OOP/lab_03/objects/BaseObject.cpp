#include "BaseObject.h"

void BaseObject::transform(std::shared_ptr<Transformer> transformer)
{
    transformMat = transformer->transform(transformMat);
}

Matrix4 BaseObject::getTransformMatrix()
{
    return Matrix4(transformMat);
}
