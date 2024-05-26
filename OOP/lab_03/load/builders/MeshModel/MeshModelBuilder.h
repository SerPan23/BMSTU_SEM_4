#ifndef MESHMODELBUILDER_H
#define MESHMODELBUILDER_H

#include <memory>

#include <ModelBuilder.h>

#include <MeshModel.h>

class MeshModelBuilder : public ModelBuilder
{
public:
    MeshModelBuilder() = default;
    ~MeshModelBuilder() = default;

    virtual bool buildVertex()  = 0;
    virtual bool buildEdge() = 0;

    virtual std::shared_ptr<BaseModel> get() = 0;

protected:
    virtual std::shared_ptr<BaseModel> create() = 0;
};

#endif // MESHMODELBUILDER_H
