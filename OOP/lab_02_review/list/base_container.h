#ifndef BASE_CONTAINTER_H
#define BASE_CONTAINTER_H

class BaseContainer
{
public:
    virtual ~BaseContainer() = default;

    virtual bool empty() const noexcept = 0;
    virtual int size() const noexcept = 0;
    virtual void clear() = 0;

protected:
    int container_size = 0;
};

#endif
