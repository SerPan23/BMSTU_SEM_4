#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <vector>
#include <map>

class AdjacencyList
{
public:
    using Indexes = std::vector<int>;
    using Iterator = std::map<int, Indexes>::iterator;

    AdjacencyList() = default;
    AdjacencyList(int firstInd, int secondInd);
    AdjacencyList(int firstInd, Indexes indexes);

    Indexes getKeys() const;

    Indexes get(int firstInd) const;

    void add(int firstInd, int index);
    void add(int firstInd, Indexes indexes);

    void remove(int firstInd);
    void remove(int firstInd, int delIndex);

    bool empty() const;

    Iterator begin();
    Iterator end();

private:
    std::map<int, Indexes> data_;
};

#endif // ADJACENCYLIST_H
