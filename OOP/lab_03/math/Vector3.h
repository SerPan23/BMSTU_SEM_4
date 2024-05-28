#ifndef VECTOR3_H
#define VECTOR3_H

#include <glm/vec3.hpp>

#include "Matrix4.h"

class Vector3
{
public:
    Vector3() = default;
    Vector3(const Vector3 &mat);
    explicit Vector3(Vector3 &&mat);
    explicit Vector3(const glm::vec3 &data_);
    Vector3(const double x, const double y, const double z);

    Vector3& operator=(const Vector3 &mat);
    Vector3& operator=(Vector3 &&mat) noexcept;

    Vector3 operator+(const Vector3 &matrix) const;
    Vector3 &operator+=(const Vector3 &matrix);

    Vector3 operator-(const Vector3 &matrix) const;
    Vector3 &operator-=(const Vector3 &matrix);

    Vector3 operator*(const Vector3 &matrix) const;
    Vector3 &operator*=(const Vector3 &matrix);

    double operator[](int i);

    glm::vec3 getData() const;

private:
    glm::vec3 data_;
};

Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs);

#endif // VECTOR3_H
