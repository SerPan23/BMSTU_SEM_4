#ifndef BASEOBJECT_H
#define BASEOBJECT_H

class BaseObject
{
public:
    BaseObject();
    virtual ~BaseObject() = default;


    virtual bool isVisible() { return false; };
    virtual bool isComposite() { return  false; };
};

#endif // BASEOBJECT_H
