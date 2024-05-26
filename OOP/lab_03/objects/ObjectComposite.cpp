#include "ObjectComposite.h"

#include "ArrayException.h"

ObjectComposite::ObjectComposite(std::shared_ptr<BaseObject> &object)
{
    objects_[objCount++] = object;
}

void ObjectComposite::accept(BaseVisitor& v)
{
    // v.visit(*this);
}

// + getTransformMatrix()
// + setTransformMatrix()

int ObjectComposite::add(const std::shared_ptr<BaseObject> &obj)
{
    objects_[objCount++] = obj;

    return objCount - 1;
}

bool ObjectComposite::remove(int objectId)
{
    auto objectToDelete = objects_.find(objectId);

    if (objectToDelete != objects_.end())
    {
        objects_.erase(objectToDelete);
        return true;
    }

    return false;
}

std::shared_ptr<BaseObject> ObjectComposite::getObject(int id)
{
    return objects_[id];
}

Iterator ObjectComposite::begin()
{
    return objects_.begin();
}

Iterator ObjectComposite::end()
{
    return objects_.end();
}
