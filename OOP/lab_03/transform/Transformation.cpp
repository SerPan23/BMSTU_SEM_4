#include "Transformation.h"

#include <QDebug>

void Transformation::operator+=(std::shared_ptr<Transformer> transformer)
{
    auto transformerPointer = transformer.get();

    if (typeid(MoveTransformer) == typeid(*transformerPointer))
        moveMatrix_ = transformer->transform(moveMatrix_);

    if (typeid(RotateTransformer) == typeid(*transformerPointer))
        RotationMatrix_ = transformer->transform(RotationMatrix_);

    if (typeid(ScaleTransformer) == typeid(*transformerPointer))
        ScaleMatrix_ = transformer->transform(ScaleMatrix_);

}

// void Transformation::operator+=(std::shared_ptr<MoveTransformer> transformer)
// {
//     moveMatrix_ = transformer->transform(moveMatrix_);
// }

// void Transformation::operator+=(std::shared_ptr<RotateTransformer> transformer)
// {
//     RotationMatrix_ = transformer->transform(RotationMatrix_);
// }

// void Transformation::operator+=(std::shared_ptr<ScaleTransformer> transformer)
// {
//     ScaleMatrix_ = transformer->transform(ScaleMatrix_);
// }

Matrix4 Transformation::getMatrix() const
{
    return moveMatrix_ * RotationMatrix_ * ScaleMatrix_;
}
