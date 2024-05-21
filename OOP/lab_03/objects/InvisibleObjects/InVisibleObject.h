#ifndef INVISIBLEOBJECT_H
#define INVISIBLEOBJECT_H

#include "BaseObject.h"

class InVisibleObject : public BaseObject
{
public:
    InVisibleObject() = default;
    ~InVisibleObject() = default;

    bool isVisible() override { return false; }
};

#endif // INVISIBLEOBJECT_H
