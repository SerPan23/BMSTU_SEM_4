#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int firstInd, int secondInd)
{
    data_[firstInd].push_back(secondInd);
}

AdjacencyList::AdjacencyList(int firstInd, Indexes indexes)
{
    data_[firstInd].insert(data_[firstInd].end(), indexes.begin(), indexes.end());
}

AdjacencyList::Indexes AdjacencyList::getKeys() const
{
    Indexes keys;
    for (const auto& element : data_)
        keys.push_back(element.first);

    return keys;
}

AdjacencyList::Indexes AdjacencyList::get(int firstInd) const
{
    return data_.at(firstInd);
}

void AdjacencyList::add(int firstInd, int index)
{
    data_[firstInd].push_back(index);
}

void AdjacencyList::add(int firstInd, Indexes indexes)
{
    data_[firstInd].insert(data_[firstInd].end(), indexes.begin(), indexes.end());
}

void AdjacencyList::remove(int firstInd)
{
    data_[firstInd].clear();
}

void AdjacencyList::remove(int firstInd, int delIndex)
{
    Indexes::iterator iter = data_[firstInd].begin() + delIndex;

    data_[firstInd].erase(iter);
}

bool AdjacencyList::empty() const
{
    return data_.empty();
}

AdjacencyList::Iterator AdjacencyList::begin()
{
    return data_.begin();
}
AdjacencyList::Iterator AdjacencyList::end()
{
    return data_.end();
}
