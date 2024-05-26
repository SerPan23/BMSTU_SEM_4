#include "BuilderSolution.h"

#include <filesystem>

#include "MeshModelBuilderFactory.h"

std::shared_ptr<ModelBuilder> create(const std::string &path, std::shared_ptr<ModelSource> source)
{
    std::filesystem::path p(path);
    std::string ext = p.extension().string();

    if (ext == "adjl")
        return MeshModelBuilderFactory::create(BuilderType::MeshAdjacencyList, source);

    return MeshModelBuilderFactory::create(BuilderType::MeshVertexEdge, source);
}
