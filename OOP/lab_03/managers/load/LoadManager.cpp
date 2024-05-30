#include "LoadManager.h"

#include "LoadException.h"
#include "ManagerSolution.h"
#include "SourceSolution.h"
#include "BuilderSolution.h"

#include "MeshModelDirector.h"

int LoadManager::loadMeshModel(const std::string &path)
{
    auto sceneManager = ManagerSolution::getSceneManager();

    auto scene = sceneManager->getScene();

    auto source = SourceSolution::create(path);

    if (source == nullptr)
        throw WrongSourceError(__FILE__, __LINE__, "Unknown source type");

    auto builder = BuilderSolution::create(path, source);

    auto director = MeshModelDirector();

    return scene->addObject(director.create(builder));
}
