#ifndef VERTEXEDGESOURCE_H
#define VERTEXEDGESOURCE_H

#include "ModelSource.h"

#include <queue>
#include <fstream>
#include <sstream>

class VertexEdgeSource : public ModelSource
{
public:
    explicit VertexEdgeSource(const std::string& path);
    virtual std::optional<Vertex> nextVertex() override;
    virtual std::optional<Edge> nextEdge() override;

private:
    std::ifstream sourceFile{};
    std::queue<Vertex> vertexQueue{};
    std::queue<Edge> edgeQueue{};

    void readVertex(std::stringstream &ss);
    void readEdge(std::stringstream &ss);
    void fileLineIter();
};

#endif // VERTEXEDGESOURCE_H
