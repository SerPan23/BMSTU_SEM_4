#ifndef ADJACENCYLISTSOURCE_H
#define ADJACENCYLISTSOURCE_H

#include "ModelSource.h"

#include <queue>
#include <fstream>
#include <sstream>

#include "AdjacencyList.h"

class AdjacencyListSource : public ModelSource
{
public:
    explicit AdjacencyListSource(const std::string& path);

    virtual std::optional<Vertex> nextVertex() override;
    virtual std::optional<Edge> nextEdge() override;

private:
    std::ifstream sourceFile{};
    std::queue<Vertex> vertexQueue{};
    std::queue<Edge> edgeQueue{};

    void readVertex(std::stringstream &ss);
    void readEdge(std::stringstream &ss);
    bool vertexEnd = false;

    void fileLineIter();
};

#endif // ADJACENCYLISTSOURCE_H
