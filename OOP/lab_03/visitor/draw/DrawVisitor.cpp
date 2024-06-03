#include "DrawVisitor.h"

#include "glm_wrapper.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera)
{
    drawer_ = std::move(drawer);
    camera_ = std::move(camera);
}
void DrawVisitor::visit(Scene &scene)
{
    for (auto& [_, i]: scene)
        if (i->isVisible())
            i->accept(*this);
}

void DrawVisitor::visit(ObjectComposite& group)
{
    Matrix4 displacement = group.getTransformMatrix();
    addTransformContext(displacement);

    for (const auto& [_, object]: group)
        object->accept(*this);

    addTransformContext(inverse(displacement));
}

void DrawVisitor::visit(MeshModel &model)
{
    const auto modelData = model.data_;

    const auto model_matrix = model.getTransformMatrix();


    Matrix4 view_matrix = camera_->getViewMatrix();
    Matrix4 projection_matrix = camera_->getProjectionMatrix();

    Matrix4 matr = projection_matrix * (view_matrix * context * model_matrix);

    const auto& vertices = modelData->getVertices();


    for (const auto& edge: modelData->getEdges())
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


void DrawVisitor::clearTransformContext()
{
    context = Matrix4(1.0);
}
void DrawVisitor::addTransformContext(const Matrix4 &ctx)
{
    context = context * ctx;
}
