#include "SourceSolution.h"

#include <filesystem>

#include "ModelSourceFactory.h"

std::shared_ptr<ModelSource> SourceSolution::create(const std::string &path)
{
    std::filesystem::path p(path);
    std::string ext = p.extension().string();

    if (ext == "ves")
        return ModelSourceFactory::create(SourceType::VertexEdge, path);
    else if (ext == "adls")
        return ModelSourceFactory::create(SourceType::AdjacencyList, path);

    return nullptr;
}
