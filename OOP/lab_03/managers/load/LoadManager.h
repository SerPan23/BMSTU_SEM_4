#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <memory>

#include <BaseManager.h>

class LoadManager : public BaseManager
{
public:
    LoadManager() = default;
    ~LoadManager() override = default;
    LoadManager(const LoadManager &) = delete;

    int loadMeshModel(const std::string &path);
};

#endif // LOADMANAGER_H
