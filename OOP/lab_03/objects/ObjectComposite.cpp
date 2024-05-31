#include "ObjectComposite.h"

#include "ArrayException.h"

ObjectComposite::ObjectComposite(std::shared_ptr<BaseObject> &object)
{
    objects_[objCount++] = object;
}

void ObjectComposite::accept(BaseVisitor& v)
{

}

int ObjectComposite::add(const std::shared_ptr<BaseObject> &obj)
{
    objects_[objCount++] = obj;

    return objCount - 1;
}

bool ObjectComposite::remove(int objectId)
{
    return objects_.erase(objectId) > 0;
}

std::shared_ptr<BaseObject> ObjectComposite::getObject(int id)
{
    return objects_.at(id);
}

Iterator ObjectComposite::begin()
{
    return objects_.begin();
}

Iterator ObjectComposite::end()
{
    return objects_.end();
}
