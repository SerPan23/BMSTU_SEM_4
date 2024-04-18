#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

template <typename T>
ListIterator<T>::ListIterator()
{   
    this->ptr.lock() = nullptr;
}
template <typename T>
ListIterator<T>::ListIterator(const std::shared_ptr<ListNode<T>> &node)
{
    this->ptr = node;
}
template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
}
template <typename T>
ListIterator<T>::ListIterator(List<T> &list)
{
    this->ptr = list.begin().ptr.lock();
}

template <typename T>
void ListIterator<T>::next(void)
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    this->ptr = this->ptr.lock()->get_next();
}
template <typename T>
bool ListIterator<T>::is_invalid() const
{
    return this->ptr.lock() == nullptr;
}

template <typename T>
std::shared_ptr<ListNode<T>> ListIterator<T>::operator->()
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    return this->ptr.lock();
}
template <typename T>
const std::shared_ptr<ListNode<T>> ListIterator<T>::operator->() const
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    return this->ptr.lock();
}

template <typename T>
T &ListIterator<T>::operator*()
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    return this->ptr.lock()->get();
}
template <typename T>
const T &ListIterator<T>::operator*() const
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    return this->ptr.lock()->get();
}

template <typename T>
ListIterator<T>::operator bool() const
{   
    return this->ptr.lock() != nullptr;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator+=(const int &size)
{
    for (int i = 0; i < size; i++)
        this->next();

    return *this;
}
template <typename T>
ListIterator<T> ListIterator<T>::operator+(const int &size) const
{
    ListIterator<T> new_iter(*this);
    new_iter += size;
    return new_iter;
}
template <typename T>
ListIterator<T> ListIterator<T>::operator=(const ListIterator<T> &iterator)
{
    if (iterator.ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    this->ptr = iterator.ptr.lock();
    return *this;
}
template <typename T>
ListIterator<T> &ListIterator<T>::operator++()
{
    this->next();
    return *this;
}
template <typename T>
ListIterator<T> ListIterator<T>::operator++(int)
{
    ListIterator<T> tmp(*this);
    this->next();
    return tmp;
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator<T> &iterator) const
{
    return this->ptr.lock() != iterator.ptr.lock();
}
template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T> &iterator) const
{
   return this->ptr.lock() == iterator.ptr.lock();
}

template <typename T>
std::shared_ptr<ListNode<T>> ListIterator<T>::get_ptr()
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    return this->ptr.lock();
}

#endif