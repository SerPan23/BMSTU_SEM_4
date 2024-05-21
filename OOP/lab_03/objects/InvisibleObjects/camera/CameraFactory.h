#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "BaseCamera.h"

#include "FPSCamera.h"

enum class CameraType
{
    FPS
};


class CameraFactory
{
public:
    CameraFactory() = delete;
    ~CameraFactory() = delete;
    CameraFactory(CameraFactory&) = delete;
    static std::shared_ptr<BaseCamera> create(const CameraType &cameraType);
};

#endif // CAMERAFACTORY_H
