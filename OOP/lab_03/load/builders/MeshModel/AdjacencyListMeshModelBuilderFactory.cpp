#include "AdjacencyListMeshModelBuilderFactory.h"
#include "AdjacencyListMeshModelBuilder.h"

std::shared_ptr<ModelBuilder> AdjacencyListMeshModelBuilderFactory::create(std::shared_ptr<ModelSource> source)
{
    return std::make_shared<AdjacencyListMeshModelBuilder>(source);
}
