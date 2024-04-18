#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

template <typename T>
ListNode<T>::ListNode()
{
    this->next = nullptr;
}
template <typename T>
ListNode<T>::ListNode(const T &data)
{
    this->next = nullptr;
    this->data = data;
}
template <typename T>
ListNode<T>::ListNode(std::shared_ptr<ListNode<T>> &node)
{
    this->next = node->next;
    this->data = node->data;
}

template <typename T>
void ListNode<T>::set(const T &data)
{
    this->data = data;
}
template <typename T>
void ListNode<T>::set_next(const ListNode<T> &node)
{
    std::shared_ptr<ListNode<T>> node_ptr(node);
    this->next = node_ptr;
}
template <typename T>
void ListNode<T>::set_next(const std::shared_ptr<ListNode<T>> &node)
{
    this->next = node;
}
template <typename T>
void ListNode<T>::set_null()
{
    this->next = nullptr;
}

template <typename T>
T &ListNode<T>::get()
{
    return this->data;
}
template <typename T>
const T &ListNode<T>::get() const
{
    return this->data;
}

template <typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::get_next() const
{
    return this->next;
}

template <typename T>
bool ListNode<T>::operator==(const std::shared_ptr<ListNode<T>> &node) const
{
    return this == node;
}
template <typename T>
bool ListNode<T>::operator!=(const std::shared_ptr<ListNode<T>> &node) const
{
    return this != node;
}

#endif