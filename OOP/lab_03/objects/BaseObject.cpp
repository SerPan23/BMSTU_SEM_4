#include "BaseObject.h"

// void BaseObject::transform(std::shared_ptr<Transformer> transformer)
// {
//     // transformMat = transformer->transform(transformMat);
//     transformation += transformer;
// }

BaseObject::BaseObject()
{
    transformation = std::make_shared<Transformation>();
}

Matrix4 BaseObject::getTransformMatrix() const
{
    // return Matrix4(transformMat);
    return transformation->getResultMatrix();
}

std::unique_ptr<Memento> BaseObject::createMemento()
{
    return std::make_unique<Memento>(*transformation.get());
}

void BaseObject::restoreMemento(std::shared_ptr<Memento> memento)
{
    if (memento != nullptr)
        transformation = std::make_shared<Transformation>(memento->getData());
}

std::shared_ptr<Transformation> BaseObject::getTransformation()
{
    return transformation;
}
