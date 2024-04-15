#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <ctime>

#include "errors.h"
#include "base_container.h"

#include "list_iterator.h"
#include "list_const_iterator.h"

#include "list_node.h"

template <typename T>
class List : public BaseContainer
{
public:
    List();
    List(List<T> &list);
    List(List<T> &&list);
    List(T *const arr, const int &size);
    List(std::initializer_list<T> nodes);
    List(const ListIterator<T> &begin, const ListIterator<T> &end);
    List(const ListConstIterator<T> &begin, const ListConstIterator<T> &end);

    ~List() override;

    bool empty() const noexcept override;
    int size() const noexcept override;
    void clear() override;

    ListIterator<T> push_front(const T& data);
    ListIterator<T> push_front(const List<T> &list);

    ListIterator<T> push_back(const T &data);
    ListIterator<T> push_back(const List<T> &list);

    ListIterator<T> insert(const ListIterator<T> &iterator, const T &data);
    ListIterator<T> insert(const ListIterator<T> &iterator, const List<T> &list);
    ListIterator<T> insert(const ListConstIterator<T> &iterator, const T &data);
    ListIterator<T> insert(const ListConstIterator<T> &iterator, const List<T> &list);

    T pop_front();
    T pop_back();
    T erase(const ListIterator<T> &iterator);

    void reverse() noexcept;

    List<T> &merge(const List<T> &list);
    List<T> &merge(const T &data);

    List<T> &operator=(const List<T> &list);
    List<T> &operator=(const List<T> &&list);

    List<T> &operator+=(const List<T> &list);
    List<T> &operator+=(const T &data);

    List<T> &operator+(const List<T> &list);
    List<T> &operator+(const T &data);

    bool operator==(const List<T> &list) const;
    bool operator!=(const List<T> &list) const;

    ListIterator<T> begin() noexcept;
    ListIterator<T> end() noexcept;

    ListConstIterator<T> cbegin() const noexcept;
    ListConstIterator<T> cend() const noexcept;

protected:
    std::shared_ptr<ListNode<T>> get_head();
    std::shared_ptr<ListNode<T>> get_tail();
    ListIterator<T> push_back(const std::shared_ptr<ListNode<T>> &node);
    ListIterator<T> push_front(const std::shared_ptr<ListNode<T>> &node);

private:
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;
};

#include "list.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, List<T> &list)
{
    ListIterator<T> iter(list);
    for (; iter; iter++)
        if (iter + 1)
            os << *iter << ", ";
        else
            os << *iter;

    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list)
{
    ListConstIterator<T> iter(list);
    for (; iter; iter++)
        if (iter + 1)
            os << *iter << ", ";
        else
            os << *iter;

    return os;
}

#endif