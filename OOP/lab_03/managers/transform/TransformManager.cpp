#include "TransformManager.h"

#include "ManagerSolution.h"

void TransformManager::move(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    //TODO: move object
}

void TransformManager::rotate(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    //TODO: rotate object
}

void TransformManager::scale(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    //TODO: scale object
}
