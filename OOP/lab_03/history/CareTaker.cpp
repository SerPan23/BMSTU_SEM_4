#include "CareTaker.h"

#include <QDebug>

std::shared_ptr<Memento> CareTaker::getMemento(int objectId)
{
    auto &states = mementos[objectId].second;

    std::shared_ptr<Memento> last = nullptr;

    if (states.size() != 0)
    {
        last = states.back();
        states.pop_back();
    }

    review();

    return last;
}

void CareTaker::setMemento(int objectId, saveData& data)
{
    mementos[objectId].first = data.first;
    mementos[objectId].second.push_back(data.second);

    review();
}

void CareTaker::review()
{
    auto tmp = mementos;

    for (auto [id, data] : tmp)
    {
        if (data.first.expired())
            mementos.erase(id);
    }
}
