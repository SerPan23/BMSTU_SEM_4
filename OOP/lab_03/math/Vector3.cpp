#include "Vector3.h"

Vector3::Vector3(const Vector3 &mat)
{
    data_ = mat.data_;
}

Vector3::Vector3(Vector3 &&mat)
{
    data_ = mat.data_;
}

Vector3::Vector3(const glm::vec3 &data)
{
    data_ = data;
}

Vector3::Vector3(const double x, const double y, const double z)
{
    data_ = {x, y, z};
}

Vector3& Vector3::operator=(const Vector3 &mat)
{
    data_ = mat.data_;

    return *this;
}

Vector3& Vector3::operator=(Vector3 &&mat) noexcept
{
    data_ = mat.data_;

    return *this;
}

Vector3 Vector3::operator+(const Vector3 &matrix) const
{
    return Vector3(this->data_ + matrix.data_);
}
Vector3& Vector3::operator+=(const Vector3 &matrix)
{
    data_ += matrix.data_;

    return *this;
}

Vector3 Vector3::operator-(const Vector3 &matrix) const
{
    return Vector3(this->data_ - matrix.data_);
}
Vector3& Vector3::operator-=(const Vector3 &matrix)
{
    data_ -= matrix.data_;

    return *this;
}

Vector3 Vector3::operator*(const Vector3 &matrix) const
{
    return Vector3(this->data_ * matrix.data_);
}
Vector3& Vector3::operator*=(const Vector3 &matrix)
{
    data_ *= matrix.data_;

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

glm::vec3 Vector3::getData() const
{
    return data_;
}

#include <glm/vec4.hpp>

Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs)
{
    glm::vec4 vec(rhs.getData(), 1.0);
    glm::vec4 result = lhs.getData() * vec;

    return Vector3(result.x, result.y, result.z);
}
