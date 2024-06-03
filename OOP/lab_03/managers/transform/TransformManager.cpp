#include "TransformManager.h"

#include "ManagerSolution.h"

#include "TransformationData.h"

void TransformManager::move(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += MoveData(param);
}

void TransformManager::rotate(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += RotationData(param);
}

void TransformManager::scale(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += ScaleData(param);
}
