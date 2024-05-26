#include "ObjectComposite.h"

#include "ArrayException.h"

ObjectComposite::ObjectComposite(std::shared_ptr<BaseObject> &object)
{
    objects_.push_back(object);
    updateCenter();
}

ObjectComposite::ObjectComposite(const std::vector<std::shared_ptr<BaseObject>> &objects)
{
    objects_ = objects;
    updateCenter();
}

void ObjectComposite::accept(BaseVisitor& v)
{
    // v.visit(*this);
}

// + getTransformMatrix()
// + setTransformMatrix()
void ObjectComposite::updateCenter()
{
    center_ = Vertex(0, 0, 0);
    size_t count = 0;

    for (const auto &obj : objects_)
    {
        center_ = center_ + obj->getCenter();
        count++;
    }

    center_ = Vertex(center_.getX() / count,
                    center_.getY() / count,
                    center_.getZ() / count);
}

int ObjectComposite::add(const std::shared_ptr<BaseObject> &obj)
{
    objects_.push_back(obj);
    updateCenter();

    return true;
}

bool ObjectComposite::remove(const Iterator &iter)
{
    objects_.erase(iter);
    updateCenter();

    return true;
}

std::shared_ptr<BaseObject> ObjectComposite::getObject(int id)
{
    if (0 > id || id >= objects_.size())
        throw IndexException(__FILE__, __LINE__, "Wrong index");

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
