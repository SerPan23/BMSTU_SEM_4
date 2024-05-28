#include "CameraCommand.h"


#include "ManagerSolution.h"

void CameraNewCommand::execute()
{
    auto manager = ManagerSolution::getCameraManager();
    cameraId = manager->newCamera();
}
int CameraNewCommand::getResult()
{
    return cameraId;
}

CameraDeleteCommand::CameraDeleteCommand(const int id)
{
    cameraId = id;
}
void CameraDeleteCommand::execute()
{
    auto manager = ManagerSolution::getCameraManager();
    manager->removeCamera(cameraId);
}

CameraSetActiveCommand::CameraSetActiveCommand(const int id)
{
    cameraId = id;
}
void CameraSetActiveCommand::execute()
{
    auto manager = ManagerSolution::getCameraManager();
    manager->setActiveCamera(cameraId);
}

CameraMoveCommand::CameraMoveCommand(const int id, Vector3 offset)
{
    cameraId = id;
    offset_ = offset;
}
void CameraMoveCommand::execute()
{
    auto manager = ManagerSolution::getCameraManager();
    manager->moveCamera(cameraId, offset_);
}

CameraRotateCommand::CameraRotateCommand(const int id, float xOffset, float yOffset)
{
    cameraId = id;
    xOffset_ = xOffset;
    yOffset_ = yOffset;
}
void CameraRotateCommand::execute()
{
    auto manager = ManagerSolution::getCameraManager();
    manager->rotateCamera(cameraId, xOffset_, yOffset_);
}
