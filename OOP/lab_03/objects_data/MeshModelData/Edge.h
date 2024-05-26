#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    Edge() = default;
    Edge(const int firstInd, const int secondInd);

    int getFirstInd() const;
    int getSecondInd() const;

    void setFirstInd(int ind);
    void setSecondInd(int ind);

private:
    int firstInd_;
    int secondInd_;
};

#endif // EDGE_H
