#ifndef MATRIX4_H
#define MATRIX4_H

#include <glm/mat4x4.hpp>

using Matrix4Data = glm::mat4;

class Matrix4
{
public:
    Matrix4() = default;
    Matrix4(const Matrix4 &mat);
    explicit Matrix4(Matrix4 &&mat);
    explicit Matrix4(const Matrix4Data &data_);
    explicit Matrix4(const double num);

    Matrix4& operator=(const Matrix4 &mat);
    Matrix4& operator=(Matrix4 &&mat) noexcept;

    Matrix4 operator+(const Matrix4 &matrix) const;
    Matrix4 &operator+=(const Matrix4 &matrix);

    Matrix4 operator-(const Matrix4 &matrix) const;
    Matrix4 &operator-=(const Matrix4 &matrix);

    Matrix4 operator*(const Matrix4 &matrix) const;
    Matrix4 &operator*=(const Matrix4 &matrix);

    Matrix4 operator/(const Matrix4 &matrix) const;
    Matrix4 &operator/=(const Matrix4 &matrix);


    Matrix4Data getData() const;

private:
    Matrix4Data data_;
};
#endif // MATRIX4_H
