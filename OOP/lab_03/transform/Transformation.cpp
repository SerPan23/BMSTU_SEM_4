#include "Transformation.h"

#include <QDebug>

Transformation::Transformation(std::shared_ptr<Transformation> transformation)
{
    moveMatrix_ = transformation->moveMatrix_;
    RotationMatrix_ = transformation->RotationMatrix_;
    ScaleMatrix_ = transformation->ScaleMatrix_;
}

void Transformation::operator+=(std::shared_ptr<MoveTransformer> transformer)
{
    moveMatrix_ = transformer->transform(moveMatrix_);
}

void Transformation::operator+=(std::shared_ptr<RotateTransformer> transformer)
{
    RotationMatrix_ = transformer->transform(RotationMatrix_);
}

void Transformation::operator+=(std::shared_ptr<ScaleTransformer> transformer)
{
    ScaleMatrix_ = transformer->transform(ScaleMatrix_);
}

Matrix4 Transformation::getResultMatrix() const
{
    return moveMatrix_ * RotationMatrix_ * ScaleMatrix_;
}


Matrix4 Transformation::getMoveMatrix() const
{
    return moveMatrix_;
}

Matrix4 Transformation::getRotationMatrix() const
{
    return RotationMatrix_;
}

Matrix4 Transformation::getScaleMatrix() const
{
    return ScaleMatrix_;
}
