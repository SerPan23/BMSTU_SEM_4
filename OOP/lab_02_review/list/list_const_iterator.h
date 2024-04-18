#ifndef LIST_CONST_ITERATOR_H
#define LIST_CONST_ITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "base_iterator.h"
#include "errors.h"

#include "list_node.h"

#include "concepts.h"

template <Comparable T>
class List;

template <typename T>
class ListConstIterator : public BaseIterator
{
public:
    ListConstIterator();
    ListConstIterator(const std::shared_ptr<ListNode<T>> &node);
    ListConstIterator(const ListConstIterator<T> &iterator);
    ListConstIterator(const List<T> &list);

    ~ListConstIterator() = default;

    void next() override;
    bool is_invalid() const override;

    const ListNode<T> *operator->() const;
    const T &operator*() const;

    operator bool() const;

    ListConstIterator<T> &operator+=(const int &size);
    ListConstIterator<T> operator+(const int &size) const;
    ListConstIterator<T> operator=(const ListConstIterator<T> &iterator);
    ListConstIterator<T> &operator++();   // префиксный
    ListConstIterator<T> operator++(int); // постфиксный

    bool operator!=(const ListConstIterator<T> &iterator) const;
    bool operator==(const ListConstIterator<T> &iterator) const;

    std::shared_ptr<ListNode<T>> get_ptr() const;

private:
    std::weak_ptr<ListNode<T>> ptr;
};

#include "list_const_iterator.hpp"

#endif