#include "CameraManager.h"

#include "ArrayException.h"
#include "CameraFactory.h"
#include "ManagerSolution.h"

#include "TraceFPSCameraAdapter.h"

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

    auto cameraId = sceneManager->addObject(camera);

    cameras_[cameraId] = camera;

    return cameraId;
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

    return sceneManager->removeObject(cameraId);
}

std::shared_ptr<BaseCamera> CameraManager::getCamera(int cameraId)
{
    return cameras_[cameraId];
}

void CameraManager::moveCamera(int cameraId, const Vector3 &offset)
{
    auto transformManager = ManagerSolution::getTransformManager();
    transformManager->move(cameraId, offset);
}

void CameraManager::rotateCamera(int cameraId, float xOffset, float yOffset)
{
    // auto camera = cameras_[cameraId];

    auto sceneManager = ManagerSolution::getSceneManager();

    auto camera = sceneManager->getObject(cameraId);
    if (!camera)
    {
        // throw BadId(__FILE__, __LINE__, "Bad id");
    }
    auto cam = dynamic_pointer_cast<FPSCamera>(camera);
    if (!cam)
    {
        // throw BadType(__FILE__, __LINE__, "Object is not a camera");
    }


    auto adapter = TraceFPSCameraAdapter(cam);
    adapter.changeTrace(xOffset, yOffset);

}

