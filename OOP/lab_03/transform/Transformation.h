#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <memory>

#include "Matrix4.h"
#include "Vector3.h"

#include "TransformationData.h"

class Transformation
{
public:
    Transformation() = default;

    explicit Transformation(std::shared_ptr<Transformation> transformation);

    Transformation(const MoveData &move, const ScaleData &scale, const RotationData &rotation);

    Transformation operator+(const MoveData& other) const;
    Transformation operator+(const ScaleData& other) const;
    Transformation operator+(const RotationData& other) const;

    Transformation& operator+=(const MoveData& other);
    Transformation& operator+=(const ScaleData& other);
    Transformation& operator+=(const RotationData& other);

    Transformation operator+(const Transformation& other) const;
    Transformation& operator+=(const Transformation& other);

    Matrix4 getResultMatrix() const;

    Matrix4 getMoveMatrix() const;
    Matrix4 getRotationMatrix() const;
    Matrix4 getScaleMatrix() const;

    Vector3 getMoveData() const;
    Vector3 getScaleData() const;
    Vector3 getRotateData() const;

private:
    MoveData move_{};
    ScaleData scale_{};
    RotationData rotation_{};
};

#endif // TRANSFORMATION_H
