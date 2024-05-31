#include "Matrix4.h"

Matrix4::Matrix4(const Matrix4 &mat)
{
    data_ = mat.data_;
}

Matrix4::Matrix4(Matrix4 &&mat)
{
    data_ = mat.data_;
}

Matrix4::Matrix4(const Matrix4Data &data)
{
    data_ = data;
}

Matrix4::Matrix4(const double num)
{
    data_ = glm::mat4(num);
}

Matrix4& Matrix4::operator=(const Matrix4 &mat)
{
    data_ = mat.data_;

    return *this;
}

Matrix4& Matrix4::operator=(Matrix4 &&mat) noexcept
{
    data_ = mat.data_;

    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4 &matrix) const
{
    return Matrix4(this->data_ + matrix.data_);
}
Matrix4& Matrix4::operator+=(const Matrix4 &matrix)
{
    data_ += matrix.data_;

    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4 &matrix) const
{
    return Matrix4(this->data_ - matrix.data_);
}
Matrix4& Matrix4::operator-=(const Matrix4 &matrix)
{
    data_ -= matrix.data_;

    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 &matrix) const
{
    return Matrix4(this->data_ * matrix.data_);
}
Matrix4& Matrix4::operator*=(const Matrix4 &matrix)
{
    data_ *= matrix.data_;

    return *this;
}

Matrix4 Matrix4::operator/(const Matrix4 &matrix) const
{
    return Matrix4(this->data_ / matrix.data_);
}
Matrix4 &Matrix4::operator/=(const Matrix4 &matrix)
{
    data_ /= matrix.data_;

    return *this;
}

Matrix4Data Matrix4::getData() const
{
    return data_;
}
