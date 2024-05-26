#ifndef ADJACENCYLISTMESHMODELBUILDER_H
#define ADJACENCYLISTMESHMODELBUILDER_H

#include "MeshModelBuilder.h"


#include "AdjacencyList.h"
#include "MeshModel.h"
#include "AdjacencyListData.h"

class AdjacencyListMeshModelBuilder : public MeshModelBuilder
{
public:
    explicit AdjacencyListMeshModelBuilder(std::shared_ptr<ModelSource> source);

    virtual bool buildVertex() override;
    virtual bool buildEdge() override;

    virtual std::shared_ptr<BaseModel> get() override;

protected:
    virtual std::shared_ptr<BaseModel> create() override;

private:
    std::vector<Vertex> vertices{};
    AdjacencyList adjacencyList{};
};

#endif // ADJACENCYLISTMESHMODELBUILDER_H
