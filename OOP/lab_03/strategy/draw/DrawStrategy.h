#ifndef DRAWSTRATEGY_H
#define DRAWSTRATEGY_H

#include <memory>

#include "BaseDrawer.h"
#include "MeshModelData.h"
#include "Matrix4.h"

class DrawStrategy
{
public:
    DrawStrategy() = default;

    virtual void draw(std::shared_ptr<BaseDrawer> drawer,
                      std::shared_ptr<MeshModelData> data, Matrix4& matr) = 0;
};

#endif // DRAWSTRATEGY_H
