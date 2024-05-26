#include "ModelSourceFactory.h"

#include "AdjacencyListSource.h"
#include "VertexEdgeSource.h"

std::shared_ptr<ModelSource> create(SourceType type, const std::string &path)
{
    if (type == SourceType::VertexEdge)
        return std::make_shared<ModelSource>(VertexEdgeSource(path));
    else if(type == SourceType::AdjacencyList)
        return std::make_shared<ModelSource>(AdjacencyListSource(path));

    return nullptr;
}
