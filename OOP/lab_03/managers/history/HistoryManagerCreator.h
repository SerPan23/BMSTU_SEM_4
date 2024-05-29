#ifndef HISTORYMANAGERCREATOR_H
#define HISTORYMANAGERCREATOR_H

#include <memory>

#include "HistoryManager.h"

class HistoryManagerCreator
{
public:
    std::shared_ptr<HistoryManager> get();

private:
    void create();
    std::shared_ptr<HistoryManager> singleton;
};

#endif // HISTORYMANAGERCREATOR_H
