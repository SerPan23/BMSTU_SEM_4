#include "FPSCamera.h"

#include "glm_wrapper.h"

FPSCamera::FPSCamera(const Vector3& position, const Vector3& up, double yaw, double pitch)
{
    position_ = position;

    Front = Vector3{0.0f, 0.0f, -1.0f};
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Matrix4 FPSCamera::getViewMatrix() const
{
    auto Position = getTransformMatrix() * position_;
    return lookAt(Position, Position + Front, Up);
}

Matrix4 FPSCamera::getProjectionMatrix()  const
{
    return perspective(radians(90.0), aspect, zNear, zFar);
}

void FPSCamera::updateCameraVectors()
{
    Vector3 front(cos(radians(Yaw)) * cos(radians(Pitch)),
                  sin(radians(Pitch)),
                  sin(radians(Yaw)) * cos(radians(Pitch)));

    Front = normalize(front);
    Right = normalize(cross(Front, WorldUp));
    Up = normalize(cross(Right, Front));
}

void FPSCamera::rotate(float x_offset, float y_offset)
{
    Yaw   += x_offset;
    Pitch += y_offset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;

    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}
