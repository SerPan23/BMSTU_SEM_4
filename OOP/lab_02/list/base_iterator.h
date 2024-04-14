#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

class BaseIterator
{
public:
    virtual ~BaseIterator() = default;

    virtual void next() = 0;
    virtual bool is_invalid() const = 0;
};

#endif