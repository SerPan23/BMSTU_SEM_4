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
    while (vertexQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (vertexQueue.empty())
        return std::nullopt;

    auto curVertex = vertexQueue.front();
    vertexQueue.pop();

    return curVertex;

    return std::nullopt;
}

std::optional<Edge> AdjacencyListSource::nextEdge()
{
    while (edgeQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (edgeQueue.empty())
        return std::nullopt;

    auto curEdge = edgeQueue.front();
    edgeQueue.pop();

    return curEdge;
}

void AdjacencyListSource::readVertex(std::stringstream &ss)
{
    double x, y, z;
    ss >> x >> y >> z;

    if (ss.fail())
        throw FileError(__FILE__, __LINE__, "Could not read vertex");

    vertexQueue.push(Vertex(x, y, z));
}

void AdjacencyListSource::readEdge(std::stringstream &ss)
{
    int firstInd, secondInd;
    ss >> firstInd;

    if (ss.fail())
        throw FileError(__FILE__, __LINE__, "Could not read first index");

    while (!ss.eof())
    {
        ss >> secondInd;

        if (ss.fail())
            throw FileError(__FILE__, __LINE__, "Could not read second index");

        edgeQueue.push(Edge(firstInd, secondInd));
    }
}

void AdjacencyListSource::fileLineIter()
{
    std::string buffer{};
    std::string str{};

    std::stringstream ss{};

    std::getline(sourceFile, buffer);

    ss.str(buffer);

    if (buffer == "vertex_end")
    {
        vertexEnd = true;
        fileLineIter();
    }
    else
    {
        if (vertexEnd)
            readEdge(ss);
        else
            readVertex(ss);
    }
}
