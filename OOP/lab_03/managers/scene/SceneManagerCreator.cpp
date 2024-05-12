#include "SceneManagerCreator.h"

void SceneManagerCreator::create()
{
    static auto manager = std::make_shared<SceneManager>();
    singleton = manager;
}

std::shared_ptr<SceneManager> SceneManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}
