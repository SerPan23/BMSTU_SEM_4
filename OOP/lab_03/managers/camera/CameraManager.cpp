#include "CameraManager.h"

#include "ArrayException.h"
#include "CameraFactory.h"
#include "CastException.h"
#include "ManagerSolution.h"

void CameraManager::setActiveCamera(int cameraId)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraObj = sceneManager->getObject(cameraId);

    if (!cameraObj)
    {
        throw IndexException(__FILE__, __LINE__, "Wrong object id");
    }

    auto camera = std::dynamic_pointer_cast<BaseCamera>(cameraObj);
    if (!camera)
    {
        throw WrongTypeException(__FILE__, __LINE__, "Object is not a camera");
    }

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

    return cameraId;
}

bool CameraManager::removeCamera(int cameraId)
{
    auto sceneManager = ManagerSolution::getSceneManager();

    return sceneManager->removeObject(cameraId);

}

std::shared_ptr<BaseCamera> CameraManager::getCamera(int cameraId)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto camera = sceneManager->getObject(cameraId);

    if (!camera)
    {
        throw IndexException(__FILE__, __LINE__, "Wrong object id");
    }

    return std::dynamic_pointer_cast<BaseCamera>(camera);
}

void CameraManager::moveCamera(int cameraId, const Vector3 &offset)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraObj = sceneManager->getObject(cameraId);

    if (!cameraObj)
    {
        throw IndexException(__FILE__, __LINE__, "Wrong object id");
    }

    auto transformManager = ManagerSolution::getTransformManager();
    transformManager->move(cameraId, offset);
}

void CameraManager::rotateCamera(int cameraId, float xOffset, float yOffset)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraObj = sceneManager->getObject(cameraId);

    if (!cameraObj)
    {
        throw IndexException(__FILE__, __LINE__, "Wrong object id");
    }

    auto transformManager = ManagerSolution::getTransformManager();
    transformManager->rotate(cameraId, Vector3(xOffset, yOffset, 0));
}

