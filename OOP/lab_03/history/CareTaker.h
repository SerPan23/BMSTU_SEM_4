#ifndef CARETAKER_H
#define CARETAKER_H

#include <memory>
#include <utility>
#include <vector>

#include "BaseObject.h"

class Memento;

class CareTaker
{
public:
    using saveData = std::pair<std::weak_ptr<BaseObject>, std::shared_ptr<Memento>>;

    std::shared_ptr<Memento> getMemento(int objectId);
    void setMemento(int objectId, saveData& data);

private:
    using MemData = std::pair<std::weak_ptr<BaseObject>, std::vector<std::shared_ptr<Memento>>>;

    void review();
    std::map<int, MemData> mementos;
};

#endif // CARETAKER_H
