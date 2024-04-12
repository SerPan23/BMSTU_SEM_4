#ifndef BASE_CONTAINTER_H
#define BASE_CONTAINTER_H

class BaseContainer
{
public:
    virtual ~BaseContainer() = default;

    virtual bool empty() const = 0;
    virtual int size() const = 0;

protected:
    int size = 0;
};

#endif
