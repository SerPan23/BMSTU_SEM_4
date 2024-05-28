#include "LoadCommand.h"

#include "ManagerSolution.h"

LoadMeshCommand::LoadMeshCommand(const std::string& path)
{
    path_ = path;
}

void LoadMeshCommand::execute()
{
    auto loadManager = ManagerSolution::getLoadManager();
    result = loadManager->loadMeshModel(path_);
}

int LoadMeshCommand::getResult()
{
    return result;
}
