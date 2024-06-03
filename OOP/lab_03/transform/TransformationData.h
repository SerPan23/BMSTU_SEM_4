#ifndef TRANSFORMATIONDATA_H
#define TRANSFORMATIONDATA_H

#include "Vector3.h"

class TransformationData
{
};

class MoveData : public TransformationData
{
public:
    float x{}, y{}, z{};
    MoveData() = default;
    MoveData(float x, float y, float z) : x(x), y(y), z(z) {};
    MoveData(const Vector3& vec) : x(vec[0]), y(vec[1]), z(vec[2]) {};
    virtual ~MoveData() = default;

    MoveData operator +(const MoveData &other) const;
    MoveData& operator +=(const MoveData &other);

    operator Vector3() const
    {
        return { x, y, z };
    };
};

class ScaleData : public TransformationData
{
public:
    float x{1}, y{1}, z{1};
    ScaleData() = default;
    ScaleData(float x, float y, float z) : x(x), y(y), z(z) {};
    ScaleData(const Vector3& vec) : x(vec[0]), y(vec[1]), z(vec[2]) {};
    virtual ~ScaleData() = default;

    ScaleData operator +(const ScaleData &other) const;
    ScaleData& operator +=(const ScaleData &other);

    operator Vector3() const
    {
        return { x, y, z };
    };
};

class RotationData : public TransformationData
{
public:
    float x{}, y{}, z{};
    RotationData() = default;
    RotationData(float x, float y, float z) : x(x), y(y), z(z) {};
    RotationData(const Vector3& vec) : x(vec[0]), y(vec[1]), z(vec[2]) {};
    virtual ~RotationData() = default;

    RotationData operator +(const RotationData &other) const;
    RotationData& operator +=(const RotationData &other);

    operator Vector3() const
    {
        return { x, y, z };
    };
};

#endif // TRANSFORMATIONDATA_H
