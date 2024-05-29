#include "DrawVisitor.h"

#include "SimpleDrawStrategy.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera)
{
    drawer_ = std::move(drawer);
    camera_ = std::move(camera);
    strategy = std::make_shared<SimpleDrawStrategy>();
}

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera, Strategy strat)
{
    drawer_ = std::move(drawer);
    camera_ = std::move(camera);
    strategy = std::move(strat);
}

void DrawVisitor::visit(Scene &scene)
{
    scene.accept(*this);
}

void DrawVisitor::visit(SceneGroup &group)
{
    for (auto &[_, object]: group)
    {
        object->accept(*this);
    }
}

void DrawVisitor::visit(MeshModel &model)
{
    const auto modelData = model.data_;

    const auto model_matrix = model.getTransformMatrix();

    Matrix4 view_matrix = camera_->getViewMatrix();
    Matrix4 projection_matrix = camera_->getProjectionMatrix();

    Matrix4 matr = projection_matrix * (view_matrix * model_matrix);

    strategy->draw(drawer_, modelData, matr);
}


void DrawVisitor::visit(LightSource &light)
{

}


void DrawVisitor::visit(BaseCamera &camera)
{

}
