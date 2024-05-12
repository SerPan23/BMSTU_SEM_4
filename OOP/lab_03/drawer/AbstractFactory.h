#ifndef ABSTARACTFACTORY_H
#define ABSTARACTFACTORY_H

#include <memory>

#include "BaseDrawer.h"


class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<BaseDrawer> create() = 0;
};

#endif // ABSTARACTFACTORY_H
