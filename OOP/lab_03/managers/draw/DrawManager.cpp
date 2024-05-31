#include "DrawManager.h"

#include "ManagerSolution.h"

#include "draw/DrawVisitor.h"

#include <QDebug>


void DrawManager::drawScene()
{
    if (not drawer)
        return;

    drawer->clear();

    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraManager = ManagerSolution::getCameraManager();
    auto scene = sceneManager->getScene();
    auto camera = cameraManager->getActiveCamera();

    DrawVisitor visitor(drawer, camera);
    visitor.visit(*scene);
}

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> &drawer_)
{
    drawer = drawer_;
}
