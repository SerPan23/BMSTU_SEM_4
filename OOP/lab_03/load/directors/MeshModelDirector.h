#ifndef MESHMODELDIRECTOR_H
#define MESHMODELDIRECTOR_H

#include <memory>

#include "MeshModel.h"
#include "MeshModelBuilder.h"

class MeshModelDirector
{
public:
    std::shared_ptr<MeshModel> create(std::shared_ptr<MeshModelBuilder> builder);
};

#endif // MESHMODELDIRECTOR_H
