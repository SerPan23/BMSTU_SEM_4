#ifndef LIST_CONST_ITERATOR_HPP
#define LIST_CONST_ITERATOR_HPP

template <typename T>
ListConstIterator<T>::ListConstIterator()
{
    this->ptr.lock() = nullptr;
}
template <typename T>
ListConstIterator<T>::ListConstIterator(const std::shared_ptr<ListNode<T>> &node)
{
    this->ptr = node;
}
template <typename T>
ListConstIterator<T>::ListConstIterator(const ListConstIterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
}
template <typename T>
ListConstIterator<T>::ListConstIterator(const List<T> &list)
{
    this->ptr = list.cbegin().ptr.lock();
}

template <typename T>
void ListConstIterator<T>::next(void)
{
    this->ptr = this->ptr.lock()->get_next();
}
template <typename T>
bool ListConstIterator<T>::is_invalid() const
{
    return this->ptr.lock() == nullptr;
}

template <typename T>
const T *ListConstIterator<T>::operator->() const
{
    return &(this->ptr.lock()->get());
}

template <typename T>
const T &ListConstIterator<T>::operator*() const
{
    return this->ptr.lock()->get();
}

template <typename T>
ListConstIterator<T>::operator bool() const
{
    return this->ptr.lock() != nullptr;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator+=(const int &size)
{
    for (int i = 0; i < size; i++)
        this->next();

    return *this;
}
template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator+(const int &size) const
{
    ListConstIterator<T> new_iter(*this);
    new_iter += size;
    return new_iter;
}
template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator=(const ListConstIterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
    return *this;
}
template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator++()
{
    this->next();
    return *this;
}
template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator++(int)
{
    ListConstIterator<T> tmp(*this);
    this->next();
    return tmp;
}

template <typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator<T> &iterator) const
{
    return this->ptr.lock() != iterator.ptr.lock();
}
template <typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator<T> &iterator) const
{
    return this->ptr.lock() == iterator.ptr.lock();
}

#endif