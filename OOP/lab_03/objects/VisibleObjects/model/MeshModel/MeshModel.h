#ifndef MESHMODEL_H
#define MESHMODEL_H

#include "BaseModel.h"

#include "MeshModelData.h"

class MeshModel : public BaseModel
{
public:
    MeshModel() = default;
    explicit MeshModel(const std::shared_ptr<MeshModelData> &data) :
        data_(data) { }
    MeshModel(const MeshModel &model);

    ~MeshModel() override = default;

    virtual void accept(BaseVisitor& v) override { v.visit(*this); };



protected:
    friend class DrawVisitor;
    std::shared_ptr<MeshModelData> data_{ nullptr };
};

#endif // MESHMODEL_H
