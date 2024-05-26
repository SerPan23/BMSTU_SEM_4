#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <memory>

#include "ModelSource.h"

#include "BaseModel.h"

class ModelBuilder
{
public:
    ModelBuilder() = default;
    ~ModelBuilder() = default;

    virtual bool buildVertex()  = 0;
    virtual bool buildEdge() = 0;

    virtual std::shared_ptr<BaseModel> get() = 0;

protected:
    virtual std::shared_ptr<BaseModel> create() = 0;

    std::shared_ptr<BaseModel> model_{ nullptr };
    std::shared_ptr<ModelSource> source_{ nullptr };
    size_t part{ 0 };
};

#endif // MODELBUILDER_H
