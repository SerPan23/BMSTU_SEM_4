#include "ObjectCommand.h"

#include "ManagerSolution.h"

ObjectDeleteCommand::ObjectDeleteCommand(int id)
{
    objectId = id;
}
void ObjectDeleteCommand::execute()
{
    auto manager = ManagerSolution::getSceneManager();
    manager->removeObject(objectId);
}

ObjectMoveCommand::ObjectMoveCommand(int id, const Vector3 &offset)
{
    objectId = id;
    offset_ = offset;
}
void ObjectMoveCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->move(objectId, offset_);
}

ObjectRotateCommand::ObjectRotateCommand(int id, const Vector3 &rotation)
{
    objectId = id;
    rotation_ = rotation;
}
void ObjectRotateCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->rotate(objectId, rotation_);
}

ObjectScaleCommand::ObjectScaleCommand(int id, const Vector3 &scale)
{
    objectId = id;
    scale_ = scale;
}
void ObjectScaleCommand::execute()
{
    auto manager = ManagerSolution::getTransformManager();
    manager->scale(objectId, scale_);
}
