#include "ManagerSolution.h"

#include "draw/DrawManagerCreator.h"
#include "scene/SceneManagerCreator.h"
#include "camera/CameraManagerCreator.h"
#include "transform/TransformManagerCreator.h"
#include "load/LoadManagerCreator.h"
#include "history/HistoryManagerCreator.h"

std::shared_ptr<DrawManager> ManagerSolution::getDrawManager()
{
    return DrawManagerCreator().get();
}

std::shared_ptr<SceneManager> ManagerSolution::getSceneManager()
{
    return SceneManagerCreator().get();
}

std::shared_ptr<CameraManager> ManagerSolution::getCameraManager()
{
    return CameraManagerCreator().get();
}

std::shared_ptr<TransformManager> ManagerSolution::getTransformManager()
{
    return TransformManagerCreator().get();
}

std::shared_ptr<LoadManager> ManagerSolution::getLoadManager()
{
    return LoadManagerCreator().get();
}

std::shared_ptr<HistoryManager> ManagerSolution::getHistoryManager()
{
    return HistoryManagerCreator().get();
}
