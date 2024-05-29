#ifndef LOGIC_H
#define LOGIC_H

#include "MetaData.h"
#include "Facade.h"

class Logic
{
public:
    Logic(std::shared_ptr<MetaData> meta) : meta(meta) {};

    void draw();

    int loadObject(const std::string &path);
    void deleteObject(int objectId);
    void deleteAllObject();

    void moveObject(int objectId, float dx, float dy, float dz);
    void rotateObject(int objectId, float dx, float dy, float dz);
    void scaleObject(int objectId, float dx, float dy, float dz);

    void moveAllObject(float dx, float dy, float dz);
    void rotateAllObject(float dx, float dy, float dz);
    void scaleAllObject(float dx, float dy, float dz);

    std::string printObjects();

    bool hasObjectId(int objectId);
    bool hasCameraId(int cameraId);

    int newCamera();
    void deleteCamera(int cameraId);

    void setActiveCamera(int cameraId);
    void moveCamera(int cameraId, float dx, float dy, float dz);
    void rotateCamera(int cameraId, float xOffset, float yOffset);

    void saveState(int objectId);
    void restoreState(int objectId);
    void restoreAllState();

private:
    Facade facade;
    std::shared_ptr<MetaData> meta;
};

#endif // LOGIC_H
