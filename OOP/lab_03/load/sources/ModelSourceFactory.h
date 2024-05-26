#ifndef MODELSOURCEFACTORY_H
#define MODELSOURCEFACTORY_H

#include <memory>
#include <string>

#include "ModelSource.h"


enum class SourceType
{
    VertexEdge,
    AdjacencyList
};

class ModelSourceFactory
{
public:
    static std::shared_ptr<ModelSource> create(SourceType type, const std::string &path);
};

#endif // MODELSOURCEFACTORY_H
