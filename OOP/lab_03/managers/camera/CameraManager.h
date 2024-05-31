#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <memory>

#include <map>

#include <BaseManager.h>

#include "BaseCamera.h"

class CameraManager : public BaseManager
{
public:
    CameraManager() = default;
    ~CameraManager() override = default;
    CameraManager(const CameraManager &) = delete;

    void setActiveCamera(int cameraId);
    std::shared_ptr<BaseCamera> getActiveCamera();

    int newCamera();
    bool removeCamera(int cameraId);

    std::shared_ptr<BaseCamera> getCamera(int cameraId);

    void moveCamera(int cameraId, const Vector3 &offset);
    void rotateCamera(int cameraId, float xOffset, float yOffset);

private:
    std::shared_ptr<BaseCamera> activeCamera_;
};

#endif // CAMERAMANAGER_H
