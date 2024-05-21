#include "CameraFactory.h"

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraType &cameraType)
{
    if (cameraType == CameraType::FPS)
        return std::make_shared<FPSCamera>(Vertex(0, 0, -100), Vertex(0, 0, 0));
}
