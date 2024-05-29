#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>

#include "BaseVisitor.h"

#include "BaseDrawer.h"
#include "Scene.h"
#include "SceneGroup.h"
#include "MeshModel.h"
#include "LightSource.h"
#include "BaseCamera.h"


#include "DrawStrategy.h"

class DrawVisitor : public BaseVisitor
{
public:
    using Strategy = std::shared_ptr<DrawStrategy>;

    DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera);
    DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera, Strategy strat);

    void visit(Scene &scene) override;
    void visit(SceneGroup &group) override;
    void visit(MeshModel &model) override;
    void visit(LightSource &light) override;
    void visit(BaseCamera &camera) override;

private:
    std::shared_ptr<BaseDrawer> drawer_;
    std::shared_ptr<BaseCamera> camera_;
    Strategy strategy;
};

#endif // DRAWVISITOR_H
