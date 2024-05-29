#ifndef MEMENTO_H
#define MEMENTO_H

#include "Transformation.h"

class Memento
{
    friend class BaseObject;
public:
    Memento() = delete;
    Memento(Transformation data) : data_(data) {};

private:
    void setData(Transformation data)
    {
        data_ = data;
    }
    Transformation getData()
    {
        return data_;
    }

    Transformation data_;
};

#endif // MEMENTO_H
