#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <BaseManager.h>

#include "CareTaker.h"

class HistoryManager : public BaseManager
{
public:

    HistoryManager() = default;
    ~HistoryManager() override = default;
    HistoryManager(const HistoryManager &) = delete;
    HistoryManager &operator=(const HistoryManager &) = delete;

    void getPrevState(int objectId);
    void saveState(int objectId);

private:
    CareTaker careTaker;
};

#endif // HISTORYMANAGER_H
