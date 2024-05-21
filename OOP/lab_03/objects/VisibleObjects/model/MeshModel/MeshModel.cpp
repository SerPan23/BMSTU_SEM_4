#include "MeshModel.h"

MeshModel::MeshModel(const MeshModel &model)
{
    data_ = model.data_;
    id_ = model.id_;
}

Vertex MeshModel::getCenter()
{
    return data_->getCenter();
}
