#include "Logic.h"

#include "Vector3.h"

#include <memory>
#include <iostream>
#include <sstream>

#include "CameraCommand.h"
#include "LoadCommand.h"
#include "ObjectCommand.h"
#include "SceneCommand.h"
#include "HistoryCommand.h"

#include <QDebug>

void Logic::draw()
{
    auto command = std::make_shared<SceneRenderCommand>();
    facade.execute(command);
}

int Logic::loadObject(const std::string &path)
{
    auto command = std::make_shared<LoadMeshCommand>(path);

    facade.execute(command);

    int result_id = command->getResult();
    meta->addObject(result_id, "Object loaded from: " + path);
    meta->setObject(result_id);

    return result_id;
}

void Logic::deleteObject(int objectId)
{
    auto command = std::make_shared<ObjectDeleteCommand>(objectId);

    facade.execute(command);

    meta->removeObject(objectId);
}

void Logic::deleteAllObject()
{

    auto objects = meta->getObjects();
    for (auto [id, _] : objects)
    {
        if (hasCameraId(id))
            continue;

        auto command = std::make_shared<ObjectDeleteCommand>(id);

        facade.execute(command);

        meta->removeObject(id);
    }
}

void Logic::moveObject(int objectId, float dx, float dy, float dz)
{
    saveState(objectId);

    auto offset = Vector3{dx, dy, dz};

    auto command = std::make_shared<ObjectMoveCommand>(objectId, offset);

    facade.execute(command);

    draw();
}

void Logic::rotateObject(int objectId, float dx, float dy, float dz)
{
    saveState(objectId);

    auto offset = Vector3{dx, dy, dz};

    auto command = std::make_shared<ObjectRotateCommand>(objectId, offset);

    facade.execute(command);

    draw();
}

void Logic::scaleObject(int objectId, float dx, float dy, float dz)
{
    saveState(objectId);

    auto offset = Vector3{dx, dy, dz};

    auto command = std::make_shared<ObjectScaleCommand>(objectId, offset);

    facade.execute(command);

    draw();
}

void Logic::moveAllObject(float dx, float dy, float dz)
{
    auto offset = Vector3{dx, dy, dz};

    for (auto [id, _] : meta->getObjects())
    {
        if (hasCameraId(id))
            continue;

        saveState(id);
        auto command = std::make_shared<ObjectMoveCommand>(id, offset);

        facade.execute(command);
    }

    draw();
}

void Logic::rotateAllObject(float dx, float dy, float dz)
{
    auto offset = Vector3{dx, dy, dz};

    for (auto [id, _] : meta->getObjects())
    {
        if (hasCameraId(id))
            continue;

        saveState(id);
        auto command = std::make_shared<ObjectRotateCommand>(id, offset);

        facade.execute(command);
    }

    draw();
}

void Logic::scaleAllObject(float dx, float dy, float dz)
{

    auto offset = Vector3{dx, dy, dz};

    for (auto [id, _] : meta->getObjects())
    {
        if (hasCameraId(id))
            continue;

        saveState(id);
        auto command = std::make_shared<ObjectScaleCommand>(id, offset);

        facade.execute(command);
    }

    draw();
}

std::string Logic::printObjects()
{
    std::stringstream ss;

    ss << "Objects in scene\n";

    for (auto &[id, desc]: meta->getObjects())
    {
        ss << "Id: " << id << " | " << desc << "\n";
    }

    return ss.str();
}

bool Logic::hasObjectId(int objectId)
{
    return meta->getObjects().find(objectId) != meta->getObjects().end();
}

bool Logic::hasCameraId(int cameraId)
{
    return meta->getCameras().find(cameraId) != meta->getCameras().end();
}

int Logic::newCamera()
{
    auto command = std::make_shared<CameraNewCommand>();
    facade.execute(command);

    int cameraId = command->getResult();
    meta->addCamera(cameraId);
    setActiveCamera(cameraId);

    return cameraId;
}

void Logic::deleteCamera(int cameraId)
{
    auto command = std::make_shared<CameraDeleteCommand>(cameraId);

    facade.execute(command);

    meta->removeCamera(cameraId);

    draw();
}

void Logic::setActiveCamera(int cameraId)
{
    auto command = std::make_shared<CameraSetActiveCommand>(cameraId);

    facade.execute(command);

    meta->setCamera(cameraId);

    draw();
}

void Logic::moveCamera(int cameraId, float dx, float dy, float dz)
{
    auto offset = Vector3(dx, dy, dz);

    auto command = std::make_shared<CameraMoveCommand>(cameraId, offset);

    facade.execute(command);

    draw();
}

void Logic::rotateCamera(int cameraId, float xOffset, float yOffset)
{
    auto command = std::make_shared<CameraRotateCommand>(cameraId, xOffset, yOffset);

    facade.execute(command);

    draw();
}

void Logic::saveState(int objectId)
{
    auto command = std::make_shared<SaveStateCommand>(objectId);

    facade.execute(command);
}

void Logic::restoreState(int objectId)
{
    auto command = std::make_shared<RestoreStateCommand>(objectId);

    facade.execute(command);

    draw();
}
void Logic::restoreAllState()
{
    for (auto [id, _] : meta->getObjects())
    {
        if (hasCameraId(id))
            continue;

        auto command = std::make_shared<RestoreStateCommand>(id);

        facade.execute(command);
    }


    draw();
}
