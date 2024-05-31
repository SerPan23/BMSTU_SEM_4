#include "MeshModelDirectorFactory.h"

#include "MeshModelDirector.h"

std::unique_ptr<ModelDirector> MeshModelDirectorFactory::create()
{
    return std::make_unique<MeshModelDirector>();
}
