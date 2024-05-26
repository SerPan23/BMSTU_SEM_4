#include "AdjacencyListSource.h"

#include "LoadException.h"

AdjacencyListSource::AdjacencyListSource(const std::string& path)
{
    sourceFile = std::ifstream(path);
    if (sourceFile.fail())
        throw FileError(__FILE__, __LINE__, "Could not open file");
}

std::optional<Vertex> AdjacencyListSource::nextVertex()
{
    // while (vertexQueue.empty() && !sourceFile.eof())
    //     fileLineIter();

    // if (vertexQueue.empty())
    //     return std::nullopt;

    // auto curVertex = vertexQueue.front();
    // vertexQueue.pop();

    // return curVertex;

    return std::nullopt;
}

std::optional<Edge> AdjacencyListSource::nextEdge()
{
    // while (edgeQueue.empty() && !sourceFile.eof())
    //     fileLineIter();

    // if (edgeQueue.empty())
    //     return std::nullopt;

    // auto curEdge = edgeQueue.front();
    // edgeQueue.pop();

    // return curEdge;

    return std::nullopt;
}
