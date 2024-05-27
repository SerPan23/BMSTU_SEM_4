#include "MetaData.h"

void MetaData::addObject(int objectId, const std::string& meta)
{
    objectMap[objectId] = meta;
    selectedObjectId = objectId;
}

void MetaData::removeObject(int objectId)
{
    objectMap.erase(objectMap.find(objectId));
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
