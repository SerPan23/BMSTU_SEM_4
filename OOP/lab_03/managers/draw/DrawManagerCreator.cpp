#include "DrawManagerCreator.h"

void DrawManagerCreator::create()
{
    static auto manager = std::make_shared<DrawManager>();
    singleton = manager;
}

std::shared_ptr<DrawManager> DrawManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}

