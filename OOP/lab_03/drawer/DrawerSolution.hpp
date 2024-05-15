#ifndef DRAWERSOLUTION_HPP
#define DRAWERSOLUTION_HPP

#include <DrawerSolution.h>

DrawerSolution::DrawerSolution(std::initializer_list<std::pair<size_t, CreateFactory>> list)
{
    for (auto elem : list)
        this->registration(elem.first, elem.second);
}

bool DrawerSolution::registration(size_t id, CreateFactory createfun)
{
    return callbacks.insert(CallBackMap::value_type(id, createfun)).second;
}

std::unique_ptr<AbstractFactory> DrawerSolution::create(size_t id)
{
    CallBackMap::const_iterator it = callbacks.find(id);

    if (it == callbacks.end())
    {
        //			throw IdError();
    }

    return std::unique_ptr<AbstractFactory>((it->second)());
}

#endif // DRAWERSOLUTION_HPP
