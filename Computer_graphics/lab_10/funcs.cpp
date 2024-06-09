#include "funcs.h"

Funcs::Funcs(std::shared_ptr<funcList> data)
{
    for (auto el : *data)
    {
        funcs[el.first] = el.second;
    }
}

void Funcs::add(std::string name, func_ptr func)
{
    funcs[name] = func;
}

void Funcs::remove(std::string name)
{
    funcs.erase(name);
}

Funcs::func_ptr Funcs::get(std::string name)
{
    return funcs[name];
}

void Funcs::clear()
{
    funcs.clear();
}

Funcs::Iterator Funcs::begin()
{
    return funcs.begin();
}

Funcs::Iterator Funcs::end()
{
    return funcs.end();
}
