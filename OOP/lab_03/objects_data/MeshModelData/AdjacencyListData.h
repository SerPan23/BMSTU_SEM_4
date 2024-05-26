#ifndef ADJACENCYLISTDATA_H
#define ADJACENCYLISTDATA_H

#include "MeshModelData.h"

#include <vector>

#include "Vertex.h"
#include "Edge.h"
#include "AdjacencyList.h"

class AdjacencyListData : public MeshModelData
{
public:
    AdjacencyListData(std::vector<Vertex> vertices, AdjacencyList adjacencyList);
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;

    void addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);

private:
    std::vector<Vertex> vertices_;
    AdjacencyList adjacencyList_;
};

#endif // ADJACENCYLISTDATA_H
