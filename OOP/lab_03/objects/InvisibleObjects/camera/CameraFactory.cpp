#include "CameraFactory.h"

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraType &cameraType)
{
    if (cameraType == CameraType::FPS)
        return std::make_shared<FPSCamera>(Vector3(0, 0, -500));

    return nullptr;
}
