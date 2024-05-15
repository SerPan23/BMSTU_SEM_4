#ifndef DRAWERSOLUTION_H
#define DRAWERSOLUTION_H


#include <memory>
#include <map>
#include <initializer_list>

#include "AbstractFactory.h"

class DrawerSolution
{
    using CreateFactory = std::unique_ptr<AbstractFactory>(*)();
    using CallBackMap = std::map<size_t, CreateFactory>;

public:
    DrawerSolution() = default;
    DrawerSolution(std::initializer_list<std::pair<size_t, CreateFactory>> list);

    bool registration(size_t id, CreateFactory createfun);
    bool check(size_t id) { return callbacks.erase(id) == 1; }

    std::unique_ptr<AbstractFactory> create(size_t id);

private:
    CallBackMap callbacks;
};

#include <DrawerSolution.hpp>

#endif // DRAWERSOLUTION_H
