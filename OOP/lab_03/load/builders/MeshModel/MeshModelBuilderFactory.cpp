#include "MeshModelBuilderFactory.h"

#include "AdjacencyListMeshModelBuilder.h"
#include "VertexEdgeMeshModelBuilder.h"

std::shared_ptr<ModelBuilder> MeshModelBuilderFactory::create(BuilderType type, std::shared_ptr<ModelSource> source)
{
    if (type == BuilderType::MeshVertexEdge)
        return std::make_shared<VertexEdgeMeshModelBuilder>(source);
    else if(type == BuilderType::MeshAdjacencyList)
        return std::make_shared<AdjacencyListMeshModelBuilder>(source);

    return nullptr;
}
