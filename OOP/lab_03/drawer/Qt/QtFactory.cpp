#include "QtFactory.h"

#include "QtDrawer.h"

QtFactory::QtFactory(std::shared_ptr<QGraphicsScene> scene_)
{
    scene = scene_;
}

std::unique_ptr<BaseDrawer> QtFactory::create()
{
    return std::make_unique<QtDrawer>(scene);
}
