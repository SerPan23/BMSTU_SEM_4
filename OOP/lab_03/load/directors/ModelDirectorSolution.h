#ifndef MODELDIRECTORSOLUTION_H
#define MODELDIRECTORSOLUTION_H

#include <memory>

#include "ModelDirector.h"

enum class ModelType
{
    MeshModel
};

class ModelDirectorSolution
{
public:
    static std::unique_ptr<ModelDirector> create(ModelType type);
};

#endif // MODELDIRECTORSOLUTION_H
