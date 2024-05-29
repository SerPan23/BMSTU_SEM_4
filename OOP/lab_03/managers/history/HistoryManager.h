#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <BaseManager.h>

class HistoryManager : public BaseManager
{
public:
public:
    HistoryManager() = default;
    ~HistoryManager() override = default;
    HistoryManager(const HistoryManager &) = delete;
    HistoryManager &operator=(const HistoryManager &) = delete;

    void getPrevState();
    void saveState();
};

#endif // HISTORYMANAGER_H
