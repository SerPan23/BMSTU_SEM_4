#ifndef MESHMODEL_H
#define MESHMODEL_H

#include "BaseModel.h"

#include "MeshModelData.h"

class MeshModel : public BaseModel
{
public:
    MeshModel() : data_(new MeshModelData) { }
    explicit MeshModel(const std::shared_ptr<MeshModelData> &data) :
        data_(data) { }
    MeshModel(const MeshModel &model);

    ~MeshModel() override = default;

    virtual Vertex getCenter() override;

protected:
    std::shared_ptr<MeshModelData> data_;
};

#endif // MESHMODEL_H
