#include "LoadManagerCreator.h"

void LoadManagerCreator::create()
{
    static auto manager = std::make_shared<LoadManager>();
    singleton = manager;
}

std::shared_ptr<LoadManager> LoadManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}

