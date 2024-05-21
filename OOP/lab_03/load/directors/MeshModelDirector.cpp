#include "MeshModelDirector.h"

std::shared_ptr<MeshModel> create(std::shared_ptr<MeshModelBuilder> builder)
{
    if (builder->buildVertex() && builder->buildEdge())
        return builder->get();

    return std::shared_ptr<MeshModel>();
}
