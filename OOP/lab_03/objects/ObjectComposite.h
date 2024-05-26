#ifndef OBJECTCOMPOSITE_H
#define OBJECTCOMPOSITE_H

#include "BaseObject.h"

class ObjectComposite : public BaseObject
{
public:
    ObjectComposite() = default;
    explicit ObjectComposite(std::shared_ptr<BaseObject> &object);

    virtual void accept(BaseVisitor& v) override;
    // + getTransformMatrix()
    // + setTransformMatrix()


    virtual int add(const std::shared_ptr<BaseObject> &) override;
    virtual bool remove(int objectId) override;

    virtual std::shared_ptr<BaseObject> getObject(int id) override;
    virtual Iterator begin() override;
    virtual Iterator end() override;
    // + createMemento()
    // + restoreMem(Memento)

private:
    // std::vector<std::shared_ptr<BaseObject>> objects_;
    ObjectMap objects_{};
    int objCount = 0;
};;

#endif // OBJECTCOMPOSITE_H
