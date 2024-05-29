#include "DrawManager.h"

#include "ManagerSolution.h"

#include "draw/DrawVisitor.h"

#include "ClipDrawStrategy.h"

void DrawManager::drawScene()
{
    if (not drawer)
        return;

    drawer->clear();

    auto scene_manager = ManagerSolution::getSceneManager();
    auto camera_manager = ManagerSolution::getCameraManager();
    auto scene = scene_manager->getScene();
    auto camera = camera_manager->getActiveCamera();

    DrawVisitor visitor(drawer, camera);
    // DrawVisitor visitor(drawer, camera, std::make_shared<ClipDrawStrategy>());
    visitor.visit(*scene);
}

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> &drawer_)
{
    drawer = drawer_;
}
