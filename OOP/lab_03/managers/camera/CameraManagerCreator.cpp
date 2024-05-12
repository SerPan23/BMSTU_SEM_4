#include "CameraManagerCreator.h"

void CameraManagerCreator::create()
{
    static auto manager = std::make_shared<CameraManager>();
    singleton = manager;
}

std::shared_ptr<CameraManager> CameraManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}
