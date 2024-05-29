#ifndef SIMPLEDRAWSTRATEGY_H
#define SIMPLEDRAWSTRATEGY_H

#include "DrawStrategy.h"

class SimpleDrawStrategy : public DrawStrategy
{
public:
    SimpleDrawStrategy() = default;

    virtual void draw(std::shared_ptr<BaseDrawer> drawer,
                      std::shared_ptr<MeshModelData> data, Matrix4& matr) override;
};

#endif // SIMPLEDRAWSTRATEGY_H
