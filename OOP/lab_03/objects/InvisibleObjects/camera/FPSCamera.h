#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "BaseCamera.h"

#include "BaseVisitor.h"

class FPSCamera : public BaseCamera
{
public:
    FPSCamera(const Vertex &pos, const Vertex &dir);

protected:
    Vertex position_;
    Vertex direction_;
};

#endif // FPSCAMERA_H
