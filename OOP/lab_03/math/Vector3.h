#ifndef VECTOR3_H
#define VECTOR3_H

#include <glm/vec3.hpp>

#include "Matrix4.h"

class Vector3
{
public:
    Vector3() = default;
    Vector3(const Vector3 &vec);
    explicit Vector3(Vector3 &&vec);
    explicit Vector3(const glm::vec3 &data_);
    Vector3(const double x, const double y, const double z);

    Vector3& operator=(const Vector3 &vec);
    Vector3& operator=(Vector3 &&vec) noexcept;

    Vector3 operator+(const Vector3 &vec) const;
    Vector3 &operator+=(const Vector3 &vec);

    Vector3 operator-(const Vector3 &vec) const;
    Vector3 &operator-=(const Vector3 &vec);

    Vector3 operator*(const Vector3 &vec) const;
    Vector3 &operator*=(const Vector3 &vec);

    double operator[](int i);
    double operator[](int i) const;

    glm::vec3 getData() const;

private:
    glm::vec3 data_;
};

Vector3 operator*(const Matrix4 &lhs, const Vector3 &rhs);

#endif // VECTOR3_H
