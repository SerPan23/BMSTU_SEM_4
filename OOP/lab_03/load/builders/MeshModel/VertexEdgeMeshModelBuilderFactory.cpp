#include "VertexEdgeMeshModelBuilderFactory.h"
#include "VertexEdgeMeshModelBuilder.h"

std::shared_ptr<ModelBuilder> VertexEdgeMeshModelBuilderFactory::create(std::shared_ptr<ModelSource> source)
{
    return std::make_shared<VertexEdgeMeshModelBuilder>(source);
}
