#include "BaseObject.h"

void BaseObject::transform(std::shared_ptr<Transformer> transformer)
{
    // transformMat = transformer->transform(transformMat);
    transformation += transformer;
}

Matrix4 BaseObject::getTransformMatrix() const
{
    // return Matrix4(transformMat);
    return transformation.getMatrix();
}
