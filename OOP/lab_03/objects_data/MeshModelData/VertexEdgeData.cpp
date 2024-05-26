#include "VertexEdgeData.h"

VertexEdgeData::VertexEdgeData(std::vector<Vertex> vertices, std::vector<Edge> edges) :
 vertices_(std::move(vertices)), edges_(std::move(edges))
{

}

const std::vector<Vertex>& VertexEdgeData::getVertices() const
{
    return vertices_;
}

const std::vector<Edge>& VertexEdgeData::getEdges() const
{
    return edges_;
}

void VertexEdgeData::addVertex(const Vertex& vertex)
{
    vertices_.push_back(vertex);
}

void VertexEdgeData::addEdge(const Edge& edge)
{
    edges_.push_back(edge);
}
