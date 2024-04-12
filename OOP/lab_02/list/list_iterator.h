#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "base_iterator.h"
#include "errors.h"

template <typename T>
class List;

template <typename T>
class ListIterator : BaseIterator
{

};

#include "list_iterator.hpp"

#endif