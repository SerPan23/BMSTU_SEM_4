#include "ModelDirectorSolution.h"

#include "MeshModelDirectorFactory.h"

std::unique_ptr<ModelDirector> ModelDirectorSolution::create(ModelType type)
{
    if (type == ModelType::MeshModel)
    {
        auto directorFactory = std::make_unique<MeshModelDirectorFactory>();
        return directorFactory->create();
    }
    return nullptr;
}
