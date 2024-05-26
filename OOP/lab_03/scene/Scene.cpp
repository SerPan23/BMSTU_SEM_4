#include "Scene.h"

Scene::Scene() : objects_(new SceneGroup) { }

int Scene::addObject(const std::shared_ptr<BaseObject> &obj)
{
    return objects_->add(obj);
}

bool Scene::removeObject(const Iterator & iter)
{
    return objects_->remove(iter);
}
bool Scene::removeObject(const int id)
{
    auto objectToDelete = objects_->getObject(id);

    for (Iterator iter = objects_->begin(); iter < objects_->end(); iter++)
        if (iter->get() == objectToDelete.get())
            return removeObject(iter);

    return false;
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
