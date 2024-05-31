#ifndef MODELSOURCE_H
#define MODELSOURCE_H

#include <optional>

#include "Vertex.h"
#include "Edge.h"

#include <string>

class ModelSource
{
public:
    virtual ~ModelSource() = default;

    virtual std::optional<Vertex> nextVertex() = 0;
    virtual std::optional<Edge> nextEdge() = 0;
};

#endif // MODELSOURCE_H
