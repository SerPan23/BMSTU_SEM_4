#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "errors.h"

template <typename T>
class ListNode
{
public:
    ListNode();
    ListNode(const T &data);
    ListNode(const std::shared_ptr<ListNode<T>> &node);

    ~ListNode() = default;

    void set(const T &data);
    void set_next(const ListNode<T> &node);
    void set_next(const std::shared_ptr<ListNode<T>> &node);
    void set_null();

    T& get();
    const T& get() const;

    std::shared_ptr<ListNode<T>> get_next() const;

    bool operator==(const std::shared_ptr<ListNode<T>> &node) const;
    bool operator!=(const std::shared_ptr<ListNode<T>> &node) const;

private:
    T data;
    std::shared_ptr<ListNode<T>> next;
};

#include "list_node.hpp"

#endif