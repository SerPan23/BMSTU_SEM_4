#ifndef MESHMODELBUILDERFACTORY_H
#define MESHMODELBUILDERFACTORY_H

#include <memory>

#include "ModelBuilder.h"


enum class BuilderType
{
    MeshVertexEdge,
    MeshAdjacencyList
};

class MeshModelBuilderFactory
{
public:
    static std::shared_ptr<ModelBuilder> create(BuilderType type, std::shared_ptr<ModelSource> source);
};

#endif // MESHMODELBUILDERFACTORY_H
