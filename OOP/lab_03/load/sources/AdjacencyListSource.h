#ifndef ADJACENCYLISTSOURCE_H
#define ADJACENCYLISTSOURCE_H

#include "ModelSource.h"

#include <queue>
#include <fstream>
#include <sstream>

class AdjacencyListSource : public ModelSource
{
public:
    explicit AdjacencyListSource(const std::string& path);

    virtual std::optional<Vertex> nextVertex() override;
    virtual std::optional<Edge> nextEdge() override;

private:
    std::ifstream sourceFile{};
    std::queue<Vertex> vertexQueue{};
};

#endif // ADJACENCYLISTSOURCE_H
