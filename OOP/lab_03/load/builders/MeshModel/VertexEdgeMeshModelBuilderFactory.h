#ifndef VERTEXEDGEMESHMODELBUILDERFACTORY_H
#define VERTEXEDGEMESHMODELBUILDERFACTORY_H

#include "MeshModelBuilderFactory.h"

class VertexEdgeMeshModelBuilderFactory : public MeshModelBuilderFactory
{
public:
    virtual std::shared_ptr<ModelBuilder> create(std::shared_ptr<ModelSource> source) override;
};

#endif // VERTEXEDGEMESHMODELBUILDERFACTORY_H
