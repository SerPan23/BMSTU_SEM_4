#ifndef CLIPDRAWSTRATEGY_H
#define CLIPDRAWSTRATEGY_H

#include "DrawStrategy.h"

#include "Vector3.h"

class ClipDrawStrategy : public DrawStrategy
{
public:
    ClipDrawStrategy() = default;

    virtual void draw(std::shared_ptr<BaseDrawer> drawer,
                      std::shared_ptr<MeshModelData> data, Matrix4& matr) override;
};

#endif // CLIPDRAWSTRATEGY_H
