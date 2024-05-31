#ifndef ADJACENCYLISTMESHMODELBUILDERFACTORY_H
#define ADJACENCYLISTMESHMODELBUILDERFACTORY_H

#include "MeshModelBuilderFactory.h"

class AdjacencyListMeshModelBuilderFactory : public MeshModelBuilderFactory
{
public:
    virtual std::shared_ptr<ModelBuilder> create(std::shared_ptr<ModelSource> source) override;
};

#endif // ADJACENCYLISTMESHMODELBUILDERFACTORY_H
