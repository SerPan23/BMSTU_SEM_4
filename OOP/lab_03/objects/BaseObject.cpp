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

std::unique_ptr<Memento> BaseObject::createMemento()
{
    return std::make_unique<Memento>(transformation);
}

void BaseObject::restoreMemento(std::shared_ptr<Memento> memento)
{
    if (memento != nullptr)
        transformation = memento->getData();
}
