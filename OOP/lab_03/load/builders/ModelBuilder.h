#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <memory>

#include "ModelSource.h"

#include "Vertex.h"
#include "Edge.h"

class ModelBuilder
{
public:
    ModelBuilder() = default;
    ~ModelBuilder() = default;

    virtual void build() = 0;
    virtual void buildPoint(const Vertex &vertex)  = 0;
    virtual void buildEdge(const Edge &edge) = 0;
    virtual bool isBuild() const = 0;

protected:
    std::shared_ptr<ModelSource> source_;
};

#endif // MODELBUILDER_H
