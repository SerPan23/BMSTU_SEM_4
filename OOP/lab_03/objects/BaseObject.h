#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <vector>
#include <memory>

#include "BaseVisitor.h"
#include "Vertex.h"

class BaseObject;

using Iterator = std::vector<std::shared_ptr<BaseObject>>::iterator;

class BaseObject
{
public:
    BaseObject()
    {
        id_ = nextId_++;
    };
    virtual ~BaseObject() = default;

    virtual int getId() { return id_; };
    virtual void accept(BaseVisitor& v) = 0;
    // + getTransformMatrix()
    // + setTransformMatrix()
    virtual void updateCenter() {};
    virtual Vertex getCenter() { return center_; }

    virtual bool isVisible() { return false; }
    virtual bool isComposite() { return  false; }

    virtual bool add(const std::shared_ptr<BaseObject> &) { return false; }
    virtual bool remove(const Iterator &) { return false; }
    virtual std::shared_ptr<BaseObject> getObject(int objectId) = 0;
    virtual Iterator begin() { return Iterator(); }
    virtual Iterator end() { return Iterator(); }
    // + createMemento()
    // + restoreMem(Memento)
protected:
    int id_;
    static int nextId_;

    Vertex center_;
};

#endif // BASEOBJECT_H
