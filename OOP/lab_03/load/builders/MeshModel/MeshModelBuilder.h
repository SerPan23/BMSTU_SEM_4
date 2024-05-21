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

    virtual void build();
    virtual void buildPoint(const Vertex &vertex);
    virtual void buildEdge(const Edge &edge);
    virtual bool isBuild() const;

    virtual std::shared_ptr<MeshModel> get();

protected:
    std::shared_ptr<MeshModel> model_;
};

#endif // MESHMODELBUILDER_H
