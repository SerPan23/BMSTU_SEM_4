#include "SceneCommand.h"

#include "ManagerSolution.h"

void SceneRenderCommand::execute()
{
    auto manager = ManagerSolution::getDrawManager();
    manager->drawScene();
}
