#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <memory>

#include "BaseManager.h"

#include "BaseDrawer.h"

class DrawManager : public BaseManager
{
public:
    DrawManager() = default;
    ~DrawManager() override = default;
    DrawManager(const DrawManager &) = delete;

    void drawScene();
    void setDrawer(std::shared_ptr<BaseDrawer> &drawer_);

private:
    std::shared_ptr<BaseDrawer> drawer;
};

#endif // DRAWMANAGER_H
