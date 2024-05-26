#ifndef OBJECTCOMPOSITE_H
#define OBJECTCOMPOSITE_H

#include "BaseObject.h"

class ObjectComposite : public BaseObject
{
public:
    ObjectComposite() = default;
    explicit ObjectComposite(std::shared_ptr<BaseObject> &object);
    explicit ObjectComposite(const std::vector<std::shared_ptr<BaseObject>> &objects);

    virtual void accept(BaseVisitor& v) override;
    // + getTransformMatrix()
    // + setTransformMatrix()
     virtual void updateCenter() override;


    virtual int add(const std::shared_ptr<BaseObject> &) override;
    virtual bool remove(const Iterator &) override;
    virtual std::shared_ptr<BaseObject> getObject(int id) override;
    virtual Iterator begin() override;
    virtual Iterator end() override;
    // + createMemento()
    // + restoreMem(Memento)

private:
    // std::vector<std::shared_ptr<BaseObject>> objects_;
};;

#endif // OBJECTCOMPOSITE_H
