#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template <typename T>
concept Comparable = requires(T a, T b) {
    a == b
};

#endif