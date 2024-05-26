#ifndef MESHMODELDIRECTOR_H
#define MESHMODELDIRECTOR_H

#include <memory>

#include "ModelDirector.h"

#include "BaseModel.h"
#include "ModelBuilder.h"

class MeshModelDirector : public ModelDirector
{
public:
    virtual std::shared_ptr<BaseModel> create(std::shared_ptr<ModelBuilder> builder) override;
};

#endif // MESHMODELDIRECTOR_H
