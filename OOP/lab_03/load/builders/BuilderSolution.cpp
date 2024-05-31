#include "BuilderSolution.h"

#include <filesystem>

#include "AdjacencyListMeshModelBuilderFactory.h"
#include "VertexEdgeMeshModelBuilderFactory.h"

#include <QDebug>

std::shared_ptr<ModelBuilder> BuilderSolution::create(const std::string &path, std::shared_ptr<ModelSource> source)
{
    std::filesystem::path p(path);
    std::string ext = p.extension().string();

    if (ext == ".adls")
    {
        auto builderFactory = std::make_unique<AdjacencyListMeshModelBuilderFactory>();
        return builderFactory->create(source);
    }

    auto builderFactory = std::make_unique<VertexEdgeMeshModelBuilderFactory>();
    return builderFactory->create(source);
}
