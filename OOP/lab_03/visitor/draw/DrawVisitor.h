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


class DrawVisitor : public BaseVisitor
{
public:
    DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera);
    void visit(Scene &scene) override;
    void visit(SceneGroup &group) override;
    void visit(MeshModel &model) override;
    void visit(LightSource &light) override;
    void visit(BaseCamera &camera) override;

private:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseCamera> camera;
};

#endif // DRAWVISITOR_H
