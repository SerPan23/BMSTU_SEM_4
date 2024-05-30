#include "DrawManager.h"

#include "ManagerSolution.h"

#include "draw/DrawVisitor.h"

#include "ClipDrawStrategy.h"

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
    // DrawVisitor visitor(drawer, camera, std::make_shared<ClipDrawStrategy>());
    visitor.visit(*scene);
}

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> &drawer_)
{
    drawer = drawer_;
}
