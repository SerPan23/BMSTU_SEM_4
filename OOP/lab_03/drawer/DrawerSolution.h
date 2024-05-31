#ifndef DRAWERSOLUTION_H
#define DRAWERSOLUTION_H

#include <memory>

#include "AbstractFactory.h"

class DrawerSolution
{
public:
    template<class Tfactory, class ...Args>
    static std::unique_ptr<BaseDrawer> create(Args &&...args)
    {
        static_assert(std::is_base_of<AbstractFactory, Tfactory>::value, "Tfactory must be derived from AbstractFactory");
        std::shared_ptr<AbstractFactory> factory = std::make_shared<Tfactory>(std::forward<Args>(args)...);
        return factory->create();
    }
};

#endif // DRAWERSOLUTION_H
