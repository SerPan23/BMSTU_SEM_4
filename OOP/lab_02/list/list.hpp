#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
List<T>::List()
{
    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}
template <typename T>
List<T>::List(List<T> &list)
{
    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node : list)
        this->push_back(node);
}
template <typename T>
List<T>::List(List<T> &&list)
{
    this->container_size = list.container_size;
    this->head = list.head;
    this->tail = list.tail;
}
template <typename T>
List<T>::List(T *const arr, const int &size)
{
    if (!arr)
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    if (size <= 0)
    {
        time_t cur_time = time(NULL);
        throw InvalidSize(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (int i = 0; i < size; i++)
        this->push_back(arr[i]);
}
template <typename T>
List<T>::List(std::initializer_list<T> nodes)
{
    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node : nodes)
        this->push_back(node);
}
template <typename T>
List<T>::List(const ListIterator<T> &begin, const ListIterator<T> &end)
{
    if (begin.is_invalid() || end.is_invalid())
    {
        time_t cur_time = time(NULL);
        throw InvalidIterator(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto current = begin; current != end + 1; current++)
        this->push_back(*current);
}
template <typename T>
List<T>::List(const ListConstIterator<T> &begin, const ListConstIterator<T> &end)
{
    if (begin.is_invalid() || end.is_invalid())
    {
        time_t cur_time = time(NULL);
        throw InvalidIterator(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto current = begin; current != end + 1; current++)
        this->push_back(*current);
}

template <typename T>
List<T>::~List()
{
    if (this->head)
        head.reset();

    if (this->tail)
        tail.reset();
}

template <typename T>
bool List<T>::empty(void) const noexcept
{
    return this->container_size == 0;
}
template <typename T>
int List<T>::size(void) const noexcept
{
    return this->container_size;
}
template <typename T>
void List<T>::clear()
{
    while (this->container_size)
        this->pop_front();
}

template <typename T>
ListIterator<T> List<T>::push_front(const std::shared_ptr<ListNode<T>> &node)
{
    if (!node)
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    node->set_next(this->head);
    this->head = node;

    if (!this->container_size)
        this->tail = this->head;

    this->container_size++;

    return ListIterator<T>(node);
}
template <typename T>
ListIterator<T> List<T>::push_front(const T &data)
{
    std::shared_ptr<ListNode<T>> tmp = nullptr;

    try
    {
        tmp = std::shared_ptr<ListNode<T>>(new ListNode<T>);
    }
    catch (std::bad_alloc &error)
    {
        time_t cur_time = time(NULL);
        throw MemoryError(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    tmp->set(data);
    return this->push_front(tmp);
}
template <typename T>
ListIterator<T> List<T>::push_front(const List<T> &list)
{
    ListIterator<T> iter;

    for (int i = 0; i < list.container_size; i++)
        iter = this->insert(this->begin() + i, (*(list.begin() + i)).get());

    return iter;
}

template <typename T>
ListIterator<T> List<T>::push_back(const std::shared_ptr<ListNode<T>> &node)
{
    if (!node)
    {
        time_t cur_time = time(NULL);
        throw InvalidPointer(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    node->set_null();

    if (!this->container_size)
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        this->tail->set_next(node);
        this->tail = node;
    }

    this->container_size++;

    return ListIterator<T>(node);
}
template <typename T>
ListIterator<T> List<T>::push_back(const T &data)
{
    std::shared_ptr<ListNode<T>> tmp = nullptr;

    try
    {
        tmp = std::shared_ptr<ListNode<T>>(new ListNode<T>);
    }
    catch (std::bad_alloc &error)
    {
        time_t cur_time = time(NULL);
        throw MemoryError(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    tmp->set(data);
    return this->push_back(tmp);
}
template <typename T>
ListIterator<T> List<T>::push_back(const List<T> &list)
{
    ListConstIterator<T> tmp_iterator = list.cbegin();
    for (; tmp_iterator + 1 != list.cend(); tmp_iterator++)
        this->push_back(*tmp_iterator);

    return ListIterator<T>(this->tail);
}

template <typename T>
ListIterator<T> List<T>::insert(const ListConstIterator<T> &iterator, const T &data)
{
    if (iterator.is_invalid())
    {
        time_t cur_time = time(NULL);
        throw InvalidIterator(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    std::shared_ptr<ListNode<T>> tmp = nullptr;

    try
    {
        tmp = std::shared_ptr<ListNode<T>>(new ListNode<T>);
    }
    catch (std::bad_alloc &error)
    {
        time_t cur_time = time(NULL);
        throw MemoryError(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    tmp->set(data);

    if (iterator == this->cbegin())
        return push_front(tmp);
    else if (iterator == this->cend())
        return this->push_back(tmp);

    ListIterator<T> tmp_iterator = this->begin();
    for (; tmp_iterator + 1 != iterator; tmp_iterator++);

    tmp->set_next(tmp_iterator->get_next());
    tmp_iterator->set_next(tmp);
    this->container_size++;

    return ListIterator<T>(tmp);
}
template <typename T>
ListIterator<T> List<T>::insert(const ListConstIterator<T> &iterator, const List<T> &list)
{
    if (iterator.is_invalid())
    {
        time_t cur_time = time(NULL);
        throw InvalidIterator(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    ListIterator<T> insert_iter;

    for (int i = 0; i < list.container_size; i++)
        insert_iter = insert(iterator, (*(list.begin() + i)).get());

    return insert_iter;
}

template <typename T>
T List<T>::pop_front(void)
{
    if (!this->container_size)
    {
        time_t cur_time = time(NULL);
        throw EmptyList(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    T data = this->head->get();

    if (this->container_size == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
        this->head = this->head->get_next();

    this->container_size--;

    return data;
}
template <typename T>
T List<T>::pop_back(void)
{
    if (!this->container_size)
    {
        time_t cur_time = time(NULL);
        throw EmptyList(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    T data = this->tail->get();

    if (this->container_size == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        std::shared_ptr<ListNode<T>> tmp = this->head;
        for (; tmp->get_next() != this->tail; tmp = tmp->get_next());

        this->tail = tmp;
        this->tail->set_null();
    }

    this->container_size--;

    return data;
}
template <typename T>
T List<T>::erase(const ListConstIterator<T> &iterator)
{
    if (iterator.is_invalid())
    {
        time_t cur_time = time(NULL);
        throw InvalidIterator(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    if (!this->container_size)
    {
        time_t cur_time = time(NULL);
        throw EmptyList(ctime(&cur_time), __FILE__, typeid(*this).name(), __LINE__);
    }

    if (iterator == this->begin())
        return pop_front();

    ListIterator<T> tmp_prev = this->begin();
    for (; tmp_prev + 1 != iterator; tmp_prev++);

    T data = tmp_prev->get_next()->get();
    tmp_prev->set_next(tmp_prev->get_next()->get_next());
    this->container_size--;

    return data;
}

template <typename T>
void List<T>::reverse(void) noexcept
{
    std::shared_ptr<ListNode<T>> current(this->head);
    std::shared_ptr<ListNode<T>> next(nullptr);
    std::shared_ptr<ListNode<T>> prev(nullptr);

    while (current)
    {
        next = current->get_next();
        current->set_next(prev);
        prev = current;
        current = next;
    }

    prev = this->head;
    this->head = this->tail;
    this->tail = prev;
    this->tail->set_null();
}

template <typename T>
List<T> &List<T>::merge(const List<T> &list)
{
    this->push_back(list);
    return *this;
}
template <typename T>
List<T> &List<T>::merge(const T &data)
{
    this->push_back(data);
    return *this;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list)
{
    this->clear();

    this->container_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    this->push_back(list);
    return *this;
}
template <typename T>
List<T> &List<T>::operator=(const List<T> &&list)
{
    this->container_size = list.container_size;
    this->head = list.head;
    this->tail = list.tail;
    return *this;
}

template <typename T>
List<T> &List<T>::operator+=(const List<T> &list)
{
    this->push_back(list);
    return *this;
}
template <typename T>
List<T> &List<T>::operator+=(const T &data)
{
    this->push_back(data);
    return *this;
}

template <typename T>
List<T> &List<T>::operator+(const List<T> &list)
{
    this->push_back(list);
    return *this;
}
template <typename T>
List<T> &List<T>::operator+(const T &data)
{
    this->push_back(data);
    return *this;
}

template <typename T>
bool List<T>::operator==(const List<T> &list) const
{
    auto tmp_this = this->cbegin();
    auto tmp_list = list.cbegin();

    for (; tmp_this != this->cend() && tmp_list != list.cend(); tmp_this++, tmp_list++)
        if (tmp_this->get() != tmp_list->get())
            return false;

    return this->container_size == list.container_size;
}
template <typename T>
bool List<T>::operator!=(const List<T> &list) const
{
    return !(this == list);
}

template <typename T>
ListIterator<T> List<T>::begin() noexcept
{
    return ListIterator<T>(this->head);
}
template <typename T>
ListIterator<T> List<T>::end() noexcept
{
    return ++ListIterator<T>(this->tail);
}

template <typename T>
ListConstIterator<T> List<T>::cbegin() const noexcept
{
    return ListConstIterator<T>(this->head);
}
template <typename T>
ListConstIterator<T> List<T>::cend() const noexcept
{
    return ++ListConstIterator<T>(this->tail);
}

template <typename T>
std::shared_ptr<ListNode<T>> List<T>::get_head()
{
    return this->head;
}
template <typename T>
std::shared_ptr<ListNode<T>> List<T>::get_tail()
{
    return this->tail;
}

#endif