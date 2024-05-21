#include "Scene.h"

Scene::Scene() : visibleObjects_(new SceneGroup), inVisibleObjects_(new SceneGroup) { }

bool Scene::addObject(std::shared_ptr<BaseObject> &obj)
{
    if (obj->isVisible())
        return visibleObjects_.get()->add(obj);

    return inVisibleObjects_.get()->add(obj);
}

bool Scene::removeObject(const Iterator & iter)
{
    if (iter->get()->isVisible())
        return visibleObjects_.get()->remove(iter);

    return inVisibleObjects_.get()->remove(iter);
}

std::shared_ptr<SceneGroup> Scene::getVisibleObjects()
{
    return visibleObjects_;
}

std::shared_ptr<SceneGroup> Scene::getInVisibleObjects()
{
    return inVisibleObjects_;
}

void Scene::accept(BaseVisitor& v)
{
    visibleObjects_->accept(v);
    inVisibleObjects_->accept(v);
}
