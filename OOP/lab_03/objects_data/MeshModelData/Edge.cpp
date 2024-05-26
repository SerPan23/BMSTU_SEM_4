#include "Edge.h"

Edge::Edge(const int firstInd, const int secondInd)
{
    firstInd_ = firstInd;
    secondInd_ = secondInd;
}

int Edge::getFirstInd() const
{
    return firstInd_;
}

int Edge::getSecondInd() const
{
    return secondInd_;
}

void Edge::setFirstInd(int ind)
{
    firstInd_ = ind;
}

void Edge::setSecondInd(int ind)
{
    secondInd_ = ind;
}
