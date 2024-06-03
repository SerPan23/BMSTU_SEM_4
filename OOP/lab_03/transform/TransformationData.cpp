#include "TransformationData.h"

MoveData MoveData::operator +(const MoveData &other) const
{
    return { x + other.x, y + other.y, z + other.z };
}
MoveData& MoveData::operator +=(const MoveData &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

ScaleData ScaleData::operator +(const ScaleData &other) const
{
    return { x * other.x, y * other.y, z * other.z };
}
ScaleData& ScaleData::operator +=(const ScaleData &other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;

    return *this;
}

RotationData RotationData::operator +(const RotationData &other) const
{
    return { x + other.x, y + other.y, z + other.z };
}
RotationData& RotationData::operator +=(const RotationData &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}
