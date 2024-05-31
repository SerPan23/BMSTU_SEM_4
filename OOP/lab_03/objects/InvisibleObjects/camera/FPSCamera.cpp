#include "FPSCamera.h"

#include "glm_wrapper.h"

#include <QDebug>

FPSCamera::FPSCamera(const Vector3& position, const Vector3& up, double yaw, double pitch)
{
    position_ = position;

    // Front = Vector3{0.0f, 0.0f, -1.0f};
    Front = Vector3{0.0f, 0.0f, 0.0f};
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Matrix4 FPSCamera::getViewMatrix() const
{

    auto Position = getTransformMatrix() * position_;
    // auto Front_ = transformation->getRotationMatrix() * Front;
    auto Front_ = getTransformMatrix() * Front;

    qDebug() << Position[0] << Position[1] << Position[2];
    qDebug() << Front_[0] << Front_[1] << Front_[2];

    return lookAt(Position, Front_, Up);
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
