#include "SimpleDrawStrategy.h"

#include "Vector3.h"

void SimpleDrawStrategy::draw(std::shared_ptr<BaseDrawer> drawer,
                              std::shared_ptr<MeshModelData> data, Matrix4 &matr)
{
    const auto& vertices = data->getVertices();

    for (const auto &edge: data->getEdges())
    {
        Vertex v1 = vertices[edge.getFirstInd()];
        Vertex v2 = vertices[edge.getSecondInd()];

        Vector3 vec1 = matr * Vector3(v1.getX(), v1.getY(), v1.getZ());
        Vector3 vec2 = matr * Vector3(v2.getX(), v2.getY(), v2.getZ());

        drawer->drawLine(
            vec1[0], vec1[1],
            vec2[0], vec2[1]);
    }
}
