#include "CameraManager.h"

#include "ArrayException.h"
#include "CameraFactory.h"
#include "ManagerSolution.h"

void CameraManager::setActiveCamera(int cameraId)
{
    auto camera = cameras_[cameraId];
    activeCamera_ = camera;
}

std::shared_ptr<BaseCamera> CameraManager::getActiveCamera()
{
    return activeCamera_;
}

int CameraManager::newCamera()
{
    auto camera = CameraFactory::create(CameraType::FPS);

    auto sceneManager = ManagerSolution::getSceneManager();

    auto camera_id = sceneManager->addObject(camera);

    cameras_[camera_id] = camera;

    return camera_id;
}

bool CameraManager::removeCamera(int cameraId)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraIt = cameras_.find(cameraId);

    if (cameraIt == cameras_.end())
        return false;

    if (cameras_.size() == 1)
        throw DeleteException(__FILE__, __LINE__, "Cannot remove the last camera");

    cameras_.erase(cameraIt);

    return sceneManager->removeObject(camearaIterators_[cameraId]);
}

std::shared_ptr<BaseCamera> CameraManager::getCamera(int cameraId)
{
    return cameras_[cameraId];
}
