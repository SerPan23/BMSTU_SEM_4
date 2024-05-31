#include "Scene.h"

int Scene::addObject(const std::shared_ptr<BaseObject> &obj)
{
    objects_[objCount++] = obj;

    return objCount - 1;
}

bool Scene::removeObject(int objectId)
{
    return objects_.erase(objectId) > 0;
}

std::shared_ptr<BaseObject> Scene::getObject(int objectId)
{
    return objects_.at(objectId);
}


void Scene::accept(BaseVisitor& v)
{
    v.visit(*this);
}


Iterator Scene::begin()
{
    return objects_.begin();
}

Iterator Scene::end()
{
    return objects_.end();
}
