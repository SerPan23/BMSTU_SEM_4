#ifndef GLM_WRAPPER_H
#define GLM_WRAPPER_H

#include <glm/vec4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

// using Vector3 = glm::vec3;
// using Vector4 = glm::vec4;
// using Matrix4 = glm::mat4;

#include "Matrix4.h"
#include "Vector3.h"

double radians(double degrees);

Matrix4 translate(const Matrix4&mat, const Vector3& offset);
Matrix4 rotate(const Matrix4&mat, float rad, const Vector3& offset);
Matrix4 scale(const Matrix4&mat, const Vector3& scale);


Matrix4 lookAt(const Vector3& pos, const Vector3& eye, const Vector3& dir);
Matrix4 perspective(float rad, float aspect, float zNear, float zFar);

Matrix4 inverse(Matrix4 mat);

Vector3 normalize(const Vector3& vec);
Vector3 cross(const Vector3 &v1, const Vector3 &v2);

#endif // GLM_WRAPPER_H
