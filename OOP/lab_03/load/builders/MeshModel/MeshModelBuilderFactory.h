#ifndef MESHMODELBUILDERFACTORY_H
#define MESHMODELBUILDERFACTORY_H

#include <memory>

#include "ModelBuilder.h"

class MeshModelBuilderFactory
{
public:
    virtual ~MeshModelBuilderFactory() = default;
    virtual std::shared_ptr<ModelBuilder> create(std::shared_ptr<ModelSource> source) = 0;
};

#endif // MESHMODELBUILDERFACTORY_H
