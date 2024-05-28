#include "MetaData.h"

void MetaData::addObject(int objectId, const std::string& meta)
{
    objectMap[objectId] = meta;
    selectedObjectId = objectId;
}

void MetaData::removeObject(int objectId)
{
    objectMap.erase(objectMap.find(objectId));

    if (objectId == selectedObjectId)
        setObject(objectMap.begin()->first);
}

void MetaData::setObject(int objectId)
{
    selectedObjectId = objectId;
}

void MetaData::setCamera(int camera)
{
    activeCamera = camera;
}

void MetaData::addCamera(int camera)
{
    cameraIds.insert(camera);
    objectMap[camera] = "BaseCamera";
}

void MetaData::removeCamera(int camera)
{
    removeObject(camera);
    for (auto it = cameraIds.begin(); it != cameraIds.end();)
    {
        if (*it == camera)
            it = cameraIds.erase(it);
        else
            ++it;
    }

    if (camera == activeCamera)
        setCamera(*cameraIds.begin());
}

std::map<int, std::string>& MetaData::getObjects()
{
    return objectMap;
}

std::set<int>& MetaData::getCameras()
{
    return cameraIds;
}

int MetaData::getSelectedObject()
{
    return selectedObjectId;
}

int MetaData::getActiveCamera()
{
    return activeCamera;
}
