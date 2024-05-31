#include "SourceSolution.h"

#include <filesystem>


#include "AdjacencyListSourceFactory.h"
#include "VertexEdgeSourceFactory.h"

std::shared_ptr<ModelSource> SourceSolution::create(const std::string &path)
{
    std::filesystem::path p(path);
    std::string ext = p.extension().string();


    if (ext == ".ves")
    {
        auto sourceFactory = std::make_unique<VertexEdgeSourceFactory>();
        return sourceFactory->create(path);
    }
    else if (ext == ".adls")
    {
        auto sourceFactory = std::make_unique<AdjacencyListSourceFactory>();
        return sourceFactory->create(path);
    }

    return nullptr;
}
