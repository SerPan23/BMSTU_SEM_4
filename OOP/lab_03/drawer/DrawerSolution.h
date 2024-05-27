#ifndef DRAWERSOLUTION_H
#define DRAWERSOLUTION_H


#include <memory>

#include "AbstractFactory.h"
#include "QtFactory.h"

enum class DrawerType
{
    QtDrawer
};

class DrawerSolution
{
public:
    DrawerSolution() = default;
    template<typename... Args>
    static std::unique_ptr<BaseDrawer> create(DrawerType type, Args &&... args)
    {
        std::unique_ptr<AbstractFactory> drawerFactory = nullptr;

        if (type == DrawerType::QtDrawer)
            drawerFactory = std::make_unique<QtFactory>(std::forward<Args>(args)...);

        return drawerFactory->create();
    }
};

#endif // DRAWERSOLUTION_H
