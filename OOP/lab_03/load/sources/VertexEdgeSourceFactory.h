#ifndef VERTEXEDGESOURCEFACTORY_H
#define VERTEXEDGESOURCEFACTORY_H

#include "ModelSourceFactory.h"

class VertexEdgeSourceFactory : public ModelSourceFactory
{
public:
    virtual std::shared_ptr<ModelSource> create(const std::string &path) override;
};

#endif // VERTEXEDGESOURCEFACTORY_H
