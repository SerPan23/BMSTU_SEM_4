#include "DrawVisitor.h"

#include "RotateTransformer.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera)
{
    drawer_ = std::move(drawer);
    camera_ = std::move(camera);
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

#include <QDebug>

void DrawVisitor::visit(MeshModel &model)
{
    const auto modelData = model.data_;
    const auto model_matrix = model.getTransformMatrix();
    const auto& vertices = modelData->getVertices();

    Matrix4 view_matrix = camera_->getViewMatrix();
    Matrix4 projection_matrix = camera_->getProjectionMatrix();

    Matrix4 matr = projection_matrix * (view_matrix * model_matrix);

    for (const auto &edge: modelData->getEdges())
    {
        Vertex v1 = vertices[edge.getFirstInd()];
        Vertex v2 = vertices[edge.getSecondInd()];

        Vector3 vec1 = matr * Vector3(v1.getX(), v1.getY(), v1.getZ());
        Vector3 vec2 = matr * Vector3(v2.getX(), v2.getY(), v2.getZ());

        drawer_->drawLine(
            vec1[0], vec1[1],
            vec2[0], vec2[1]);
    }
}


void DrawVisitor::visit(LightSource &light)
{

}


void DrawVisitor::visit(BaseCamera &camera)
{

}
