#ifndef MODELDIRECTOR_H
#define MODELDIRECTOR_H

#include <memory>

#include "BaseModel.h"
#include "ModelBuilder.h"

class ModelDirector
{
public:
    virtual ~ModelDirector() = default;
    virtual std::shared_ptr<BaseModel> create(std::shared_ptr<ModelBuilder> builder) = 0;
};

#endif // MODELDIRECTOR_H
