#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>

#include "BaseVisitor.h"

#include "BaseDrawer.h"
#include "Scene.h"
#include "ObjectComposite.h"
#include "MeshModel.h"
#include "LightSource.h"
#include "BaseCamera.h"


class DrawVisitor : public BaseVisitor
{
public:
    DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera);

    void visit(Scene &scene) override;
    void visit(ObjectComposite& group) override;
    void visit(MeshModel &model) override;
    void visit(LightSource &light) override;
    void visit(BaseCamera &camera) override;

private:
    std::shared_ptr<BaseDrawer> drawer_;
    std::shared_ptr<BaseCamera> camera_;
    Matrix4 context{1.0};
    void clearTransformContext();
    void addTransformContext(const Matrix4 &ctx);
};

#endif // DRAWVISITOR_H
