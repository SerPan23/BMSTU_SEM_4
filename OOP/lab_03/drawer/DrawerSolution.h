#ifndef DRAWERSOLUTION_H
#define DRAWERSOLUTION_H


#include <memory>

#include "BaseDrawer.h"
#include "AbstractFactory.h"

#include "Qt/QtDrawer.h"
#include "Qt/QtFactory.h"

enum class DrawerType
{
    QtDrawer
};

class CanvasSolution
{
public:

    template<typename... Args>
    static std::unique_ptr<BaseDrawer> create(DrawerType type, Args &&... args)
    {
        std::unique_ptr<AbstractFactory> factory = nullptr;

        if (type == DrawerType::QtDrawer)
            factory = std::make_unique<QtFactory>(std::forward<Args>(args)...);

        return factory->create();
    }
};

#endif // DRAWERSOLUTION_H
