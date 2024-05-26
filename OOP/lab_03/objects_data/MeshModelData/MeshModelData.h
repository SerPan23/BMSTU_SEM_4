#ifndef MESHMODELDATA_H
#define MESHMODELDATA_H

#include <vector>

#include "Vertex.h"
#include "Edge.h"

class MeshModelData
{
public:
    MeshModelData() = default;

    virtual const std::vector<Vertex>& getVertices() const = 0;
    virtual const std::vector<Edge>& getEdges() const = 0;

    virtual void addVertex(const Vertex& vertex) = 0;
    virtual void addEdge(const Edge& edge) = 0;
};

#endif // MESHMODELDATA_H
