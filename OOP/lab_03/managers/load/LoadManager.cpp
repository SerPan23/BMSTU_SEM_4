#include "LoadManager.h"

#include "ManagerSolution.h"
#include "SourceSolution.h"
#include "BuilderSolution.h"

#include "MeshModelDirector.h"

int LoadManager::loadMeshModel(const std::string &path)
{
    auto sceneManager = ManagerSolution::getSceneManager();

    auto scene = sceneManager->getScene();

    auto source = SourceSolution::create(path);

    auto builder = BuilderSolution::create(path, source);

    auto director = MeshModelDirector();

    return scene->addObject(director.create(builder));
}
