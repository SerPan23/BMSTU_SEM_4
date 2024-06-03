#include "TraceFPSCameraAdapter.h"

#include <QDebug>

void TraceFPSCameraAdapter::changeTrace(float xOffset, float yOffset)
{
    adaptee->Yaw += xOffset;
    adaptee->Pitch += yOffset;

    if(adaptee->Pitch > 89.0f)
        adaptee->Pitch = 89.0f;
    if(adaptee->Pitch < -89.0f)
        adaptee->Pitch = -89.0f;

    // Vector3 front(
    //     cos(radians(adaptee->Yaw)) * cos(radians(adaptee->Pitch)),
    //     sin(radians(adaptee->Pitch)),
    //     sin(radians(adaptee->Yaw)) * cos(radians(adaptee->Pitch)));

    Vector3 front(
        cos(radians(adaptee->Yaw)) * cos(radians(adaptee->Pitch)),
        sin(radians(adaptee->Pitch)),
        sin(radians(adaptee->Yaw)) * cos(radians(adaptee->Pitch)));

    adaptee->Front = normalize(front);
}
