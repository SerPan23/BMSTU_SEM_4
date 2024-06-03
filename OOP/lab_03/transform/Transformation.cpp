#include "Transformation.h"

#include <QDebug>

#include "glm_wrapper.h"

Transformation::Transformation(std::shared_ptr<Transformation> transformation)
{
    move_ = transformation->move_;
    rotation_ = transformation->rotation_;
    scale_ = transformation->scale_;
}

Transformation::Transformation(const MoveData &move, const ScaleData &scale, const RotationData &rotation)
{
    move_ = move;
    rotation_ = rotation;
    scale_ = scale;
}

Transformation Transformation::operator+(const MoveData& other) const
{
    return { move_ + other, scale_, rotation_};
}
Transformation Transformation::operator+(const ScaleData& other) const
{
    return { move_, scale_ + other, rotation_};
}
Transformation Transformation::operator+(const RotationData& other) const
{
    return { move_, scale_, rotation_ + other};
}

Transformation& Transformation::operator+=(const MoveData& other)
{
    move_ += other;
    return *this;
}

Transformation& Transformation::operator+=(const ScaleData& other)
{
    scale_ += other;
    return *this;
}

Transformation& Transformation::operator+=(const RotationData& other)
{
    rotation_ += other;
    return *this;
}

Transformation Transformation::operator+(const Transformation& other) const
{
    return { move_ + other.move_, scale_ + other.scale_, rotation_ + other.rotation_};
}
Transformation& Transformation::operator+=(const Transformation& other)
{
    move_ += other.move_;
    scale_ += other.scale_;
    rotation_ += other.rotation_;

    return *this;
}


Matrix4 Transformation::getResultMatrix() const
{
    return getMoveMatrix() * getRotationMatrix() * getScaleMatrix();
}


Matrix4 Transformation::getMoveMatrix() const
{    
    Matrix4 model(1.0);

    return translate(model, move_);
}

Matrix4 Transformation::getRotationMatrix() const
{
    Matrix4 model(1.0);
    model = rotate(model, radians(rotation_.x), Vector3(1.0, 0.0, 0.0));
    model = rotate(model, radians(rotation_.y), Vector3(0.0, 1.0, 0.0));
    model = rotate(model, radians(rotation_.z), Vector3(0.0, 0.0, -1.0));

    return model;
}

Matrix4 Transformation::getScaleMatrix() const
{
    Matrix4 model(1.0);

    return scale(model, scale_);
}

Vector3 Transformation::getMoveData() const
{
    return move_;
}
Vector3 Transformation::getScaleData() const
{
    return scale_;
}
Vector3 Transformation::getRotateData() const
{
    return rotation_;
}
