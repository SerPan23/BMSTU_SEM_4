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

    virtual const std::vector<Vertex>& getVertices() const override;
    virtual const std::vector<Edge>& getEdges() const override;

    virtual void addVertex(const Vertex& vertex) override;
    virtual void addEdge(const Edge& edge) override;

private:
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
};

#endif // VERTEXEDGEDATA_H
