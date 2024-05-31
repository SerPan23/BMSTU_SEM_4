#include "VertexEdgeSourceFactory.h"

#include "VertexEdgeSource.h"


std::shared_ptr<ModelSource> VertexEdgeSourceFactory::create(const std::string &path)
{
    return std::make_shared<VertexEdgeSource>(path);
}
