#include "MeshModelDirector.h"

std::shared_ptr<BaseModel> MeshModelDirector::create(std::shared_ptr<ModelBuilder> builder)
{
    if (builder->buildVertex() && builder->buildEdge())
        return builder->get();

    return nullptr;
}
