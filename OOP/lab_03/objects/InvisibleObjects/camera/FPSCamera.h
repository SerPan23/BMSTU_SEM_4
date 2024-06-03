#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "BaseCamera.h"

#include "BaseVisitor.h"

constexpr const double YAW = -90.0;
constexpr const double PITCH =  0.0;
constexpr const double MAX_YAW = 360.0;
constexpr const double MIN_YAW = -360.0;

constexpr const double MAX_PITCH = 89.0;
constexpr const double MIN_PITCH = -89.0;

constexpr const double MAX_ROLL = 180.0;
constexpr const double MIN_ROLL = -180.0;

class FPSCamera : public BaseCamera
{
public:
    FPSCamera(const Vector3 &position, const Vector3&up=Vector3{0, 1, 0}, double yaw=YAW, double pitch=PITCH);


protected:
    virtual Matrix4 getViewMatrix() override;
    virtual Matrix4 getProjectionMatrix()  const override;

    Vector3 position_{};
    Vector3 Front{};
    Vector3 Up{};
    Vector3 Right{};
    Vector3 WorldUp{};
    float Yaw;
    float Pitch;
    float aspect = 1.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    void updateCameraVectors();


};

#endif // FPSCAMERA_H
