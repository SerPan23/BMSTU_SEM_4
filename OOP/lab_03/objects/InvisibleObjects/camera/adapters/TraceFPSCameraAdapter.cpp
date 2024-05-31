#include "TraceFPSCameraAdapter.h"

#include <QDebug>

void TraceFPSCameraAdapter::changeTrace(float xOffset, float yOffset)
{
    auto newTransformation = Transformation();

    newTransformation += std::make_shared<RotateTransformer>(xOffset, yOffset, 1);

    auto tmp =  newTransformation.getRotationMatrix() * adaptee->Front;


    qDebug() << "Params" << xOffset << yOffset;
    qDebug() << "SF" << adaptee->Front[0] << adaptee->Front[1] << adaptee->Front[2];
    qDebug() << "NF" << tmp[0] << tmp[1] << tmp[2] << "\n";

    adaptee->Front = newTransformation.getRotationMatrix() * adaptee->Front;
}
