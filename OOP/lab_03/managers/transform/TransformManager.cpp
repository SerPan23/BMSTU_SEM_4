#include "TransformManager.h"

#include "ManagerSolution.h"

#include "MoveTransformer.h"
#include "RotateTransformer.h"
#include "ScaleTransformer.h"

void TransformManager::move(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += std::make_shared<MoveTransformer>(param[0], param[1], param[2]);
}

void TransformManager::rotate(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += std::make_shared<RotateTransformer>(param[0], param[1], param[2]);
}

void TransformManager::scale(int objectId, const Vector3 &param) const
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto scene = sceneManager->getScene();
    auto object = scene->getObject(objectId);

    *object->getTransformation() += std::make_shared<ScaleTransformer>(param[0], param[1], param[2]);
}
