#ifndef BASEOBJECT_H
#define BASEOBJECT_H

// #include <vector>
#include <map>
#include <memory>

#include "BaseVisitor.h"
#include "Vertex.h"

class BaseObject;

// using Iterator = std::vector<std::shared_ptr<BaseObject>>::iterator;
using ObjectMap = std::map<int, std::shared_ptr<BaseObject>>;
using Iterator = ObjectMap::iterator;

class BaseObject
{
public:
    BaseObject() = default;
    virtual ~BaseObject() = default;

    virtual void accept(BaseVisitor& v) {};
    // + getTransformMatrix()
    // + setTransformMatrix()

    virtual bool isVisible() { return false; }
    virtual bool isComposite() { return  false; }

    virtual int add(const std::shared_ptr<BaseObject> &) { return false; }
    virtual bool remove(int objectId) { return false; }

    virtual std::shared_ptr<BaseObject> getObject(int objectId) {return nullptr; };

    virtual Iterator begin() { return Iterator(); }
    virtual Iterator end() { return Iterator(); }
    // + createMemento()
    // + restoreMem(Memento)
protected:
    Vertex center_;
};

#endif // BASEOBJECT_H
