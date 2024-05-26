#ifndef VERTEXEDGEDATA_H
#define VERTEXEDGEDATA_H

#include "MeshModelData.h"

#include <vector>

#include "Vertex.h"
#include "Edge.h"

class VertexEdgeData : public MeshModelData
{
public:
    VertexEdgeData(std::vector<Vertex> vertices, std::vector<Edge> edges);
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;

    void addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);

private:
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
};

#endif // VERTEXEDGEDATA_H
