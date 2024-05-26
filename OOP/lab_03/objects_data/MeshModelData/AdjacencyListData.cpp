#include "AdjacencyListData.h"

AdjacencyListData::AdjacencyListData(std::vector<Vertex> vertices, AdjacencyList adjacencyList) :
    vertices_(std::move(vertices)), adjacencyList_(std::move(adjacencyList))
{

}

const std::vector<Vertex>& AdjacencyListData::getVertices() const
{
    return vertices_;
}

const std::vector<Edge>& AdjacencyListData::getEdges() const
{
    static std::vector<Edge> edges;
    edges.clear();

    for (const auto& firstInd : adjacencyList_.getKeys())
    {
        auto indexes = adjacencyList_.get(firstInd);
        for (const auto& index : indexes)
            edges.push_back(Edge(firstInd, index));
    }

    return edges;
}

void AdjacencyListData::addVertex(const Vertex& vertex)
{
    vertices_.push_back(vertex);
}

void AdjacencyListData::addEdge(const Edge& edge)
{
    adjacencyList_.add(edge.getFirstInd(), edge.getSecondInd());
}
