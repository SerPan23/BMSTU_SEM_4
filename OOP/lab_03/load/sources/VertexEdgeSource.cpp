#include "VertexEdgeSource.h"

#include "LoadException.h"

VertexEdgeSource::VertexEdgeSource(const std::string& path)
{
    sourceFile = std::ifstream(path);
    if (sourceFile.fail())
        throw FileError(__FILE__, __LINE__, "Could not open file");
}

std::optional<Vertex> VertexEdgeSource::nextVertex()
{
    while (vertexQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (vertexQueue.empty())
        return std::nullopt;

    auto curVertex = vertexQueue.front();
    vertexQueue.pop();

    return curVertex;
}

std::optional<Edge> VertexEdgeSource::nextEdge()
{
    while (edgeQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (edgeQueue.empty())
        return std::nullopt;

    auto curEdge = edgeQueue.front();
    edgeQueue.pop();

    return curEdge;
}


void VertexEdgeSource::readVertex(std::stringstream &ss)
{
    double x, y, z;
    ss >> x >> y >> z;

    if (ss.fail())
        throw FileError(__FILE__, __LINE__, "Could not read vertex");

    vertexQueue.push(Vertex(x, y, z));
}

void VertexEdgeSource::readEdge(std::stringstream &ss)
{
    int firstInd, secondInd;
    ss >> firstInd >> secondInd;

    if (ss.fail())
        throw FileError(__FILE__, __LINE__, "Could not read edge");

    edgeQueue.push(Edge(firstInd, secondInd));
}

void VertexEdgeSource::fileLineIter()
{
    std::string buffer{};
    std::string prefix{};
    std::stringstream ss{};

    std::getline(sourceFile, buffer);
    ss.str(buffer);
    ss >> prefix;

    if (prefix == "e")
        readEdge(ss);

    if (prefix == "v")
        readVertex(ss);
}
