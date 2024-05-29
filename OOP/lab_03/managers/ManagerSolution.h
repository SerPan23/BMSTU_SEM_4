#ifndef MANAGERSOLUTION_H
#define MANAGERSOLUTION_H

#include <memory>

#include "draw/DrawManager.h"
#include "scene/SceneManager.h"
#include "camera/CameraManager.h"
#include "transform/TransformManager.h"
#include "load/LoadManager.h"
#include "history/HistoryManager.h"


class ManagerSolution
{
public:
    ManagerSolution() = delete;
    ~ManagerSolution() = delete;
    ManagerSolution(ManagerSolution &) = delete;


    static std::shared_ptr<DrawManager> getDrawManager();
    static std::shared_ptr<SceneManager> getSceneManager();
    static std::shared_ptr<CameraManager> getCameraManager();
    static std::shared_ptr<TransformManager> getTransformManager();
    static std::shared_ptr<LoadManager> getLoadManager();

    static std::shared_ptr<HistoryManager> getHistoryManager();
};

#endif // MANAGERSOLUTION_H
