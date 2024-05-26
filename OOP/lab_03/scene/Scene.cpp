#include "Scene.h"

Scene::Scene() : objects_(new SceneGroup) { }

int Scene::addObject(const std::shared_ptr<BaseObject> &obj)
{
    return objects_->add(obj);
}

bool Scene::removeObject(int objectId)
{
    return objects_->remove(objectId);
}

std::shared_ptr<BaseObject> Scene::getObject(int objectId)
{
    return objects_->getObject(objectId);
}

std::shared_ptr<SceneGroup> Scene::getObjects()
{
    return objects_;
}


void Scene::accept(BaseVisitor& v)
{
    objects_->accept(v);
}
