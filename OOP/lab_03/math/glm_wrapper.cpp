#include "glm_wrapper.h"

double radians(double degrees)
{
    return (double)(degrees * M_PI / 180.0);
}

Matrix4 translate(const Matrix4&mat, const Vector3& offset)
{
    return Matrix4(glm::translate(mat.getData(), offset.getData()));
}

Matrix4 rotate(const Matrix4&mat, float rad, const Vector3& offset)
{
    return Matrix4(glm::rotate(mat.getData(), rad, offset.getData()));
}

Matrix4 scale(const Matrix4&mat, const Vector3& scale)
{
    return Matrix4(glm::scale(mat.getData(), scale.getData()));
}

Matrix4 lookAt(const Vector3& pos, const Vector3& eye, const Vector3& dir)
{
    return Matrix4(glm::lookAt(pos.getData(), eye.getData(), dir.getData()));
}

Matrix4 inverse(Matrix4 mat)
{
    return Matrix4(glm::inverse(mat.getData()));
}

Vector3 normalize(const Vector3& vec)
{
    return Vector3(glm::normalize(vec.getData()));
}

Matrix4 perspective(float rad, float aspect, float zNear, float zFar)
{
    return Matrix4(glm::perspective(rad, aspect, zNear, zFar));
}

Vector3 cross(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(glm::cross(v1.getData(), v2.getData()));
}
