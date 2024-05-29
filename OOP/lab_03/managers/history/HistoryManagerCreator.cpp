#include "HistoryManagerCreator.h"

void HistoryManagerCreator::create()
{
    static auto manager = std::make_shared<HistoryManager>();
    singleton = manager;
}

std::shared_ptr<HistoryManager> HistoryManagerCreator::get()
{
    if (not singleton) create();
    return singleton;
}
