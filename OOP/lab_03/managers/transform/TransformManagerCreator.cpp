#include "TransformManagerCreator.h"

void TransformManagerCreator::create()
{
    static auto manager = std::make_shared<TransformManager>();
    singleton = manager;
}

std::shared_ptr<TransformManager> TransformManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}
