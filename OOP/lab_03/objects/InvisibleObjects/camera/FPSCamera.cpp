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
    return lookAt(position_, position_ + Front, Up);
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
    Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = normalize(cross(Right, Front));
}
