#include "Vector3.h"

#include <glm/vec4.hpp>

Vector3::Vector3(const Vector3 &vec)
{
    data_ = vec.data_;
}

Vector3::Vector3(Vector3 &&vec)
{
    data_ = vec.data_;
}

Vector3::Vector3(const Vector3Data &data)
{
    data_ = data;
}

Vector3::Vector3(const double x, const double y, const double z)
{
    data_ = {x, y, z};
}

Vector3& Vector3::operator=(const Vector3 &vec)
{
    data_ = vec.data_;

    return *this;
}

Vector3& Vector3::operator=(Vector3 &&vec) noexcept
{
    data_ = vec.data_;

    return *this;
}

Vector3 Vector3::operator+(const Vector3 &vec) const
{
    return Vector3(this->data_ + vec.data_);
}
Vector3& Vector3::operator+=(const Vector3 &vec)
{
    data_ += vec.data_;

    return *this;
}

Vector3 Vector3::operator-(const Vector3 &vec) const
{
    return Vector3(this->data_ - vec.data_);
}
Vector3& Vector3::operator-=(const Vector3 &vec)
{
    data_ -= vec.data_;

    return *this;
}

Vector3 Vector3::operator*(const Vector3 &vec) const
{
    return Vector3(this->data_ * vec.data_);
}
Vector3& Vector3::operator*=(const Vector3 &vec)
{
    data_ *= vec.data_;

    return *this;
}

double Vector3::operator[](int i)
{
    return data_[i];
}

double Vector3::operator[](int i) const
{
    return data_[i];
}

Vector3Data Vector3::getData() const
{
    return data_;
}

Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs)
{
    glm::vec4 vec(rhs.getData(), 1.0);
    glm::vec4 result = lhs.getData() * vec;

    return Vector3(result.x, result.y, result.z);
}
