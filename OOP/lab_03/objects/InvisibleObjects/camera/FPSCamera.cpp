#include "FPSCamera.h"

#include "glm_wrapper.h"

#include <QDebug>

FPSCamera::FPSCamera(const Vector3& position, const Vector3& up, double yaw, double pitch)
{
    position_ = position;

    Front = Vector3{0.0f, 0.0f, -1.0f};
    // Front = Vector3{0.0f, 0.0f, 0.0f};
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    *transformation += RotationData(Yaw, Pitch, 0);

    updateCameraVectors();
}

Matrix4 FPSCamera::getViewMatrix()
{
    auto Position = transformation->getMoveMatrix() * position_;

    auto gyro = transformation->getRotateData();


    // gyro =  Vector3(
    //     std::clamp(gyro[0], MIN_YAW, MAX_YAW),
    //     std::clamp(gyro[1], MIN_PITCH, MAX_PITCH),
    //     std::clamp(gyro[2], MIN_ROLL, MAX_ROLL));
    // Vector3 Front_ = normalize(
    //     Vector3(
    //     cos(radians(gyro[0])) * cos(radians(gyro[1])),
    //     sin(radians(gyro[1])),
    //     sin(radians(gyro[0])) * cos(radians(gyro[1]))));

    Yaw = std::clamp(gyro[0], MIN_YAW, MAX_YAW);
    Pitch = std::clamp(gyro[1], MIN_PITCH, MAX_PITCH);

    updateCameraVectors();

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
