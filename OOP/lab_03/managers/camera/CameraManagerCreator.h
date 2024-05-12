#ifndef CAMERAMANAGERCREATOR_H
#define CAMERAMANAGERCREATOR_H

#include "CameraManager.h"

class CameraManagerCreator
{
public:
    std::shared_ptr<CameraManager> get();
private:
    void create();
    std::shared_ptr<CameraManager> singleton;
};

#endif // CAMERAMANAGERCREATOR_H
