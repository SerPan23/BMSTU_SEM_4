#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "BaseCamera.h"

class FPSCamera : public BaseCamera
{
public:
    FPSCamera() = default;
    FPSCamera(const Vertex &pos, const Vertex &dir) : direction_(dir)
    { position_ = pos; }

protected:
    Vertex direction_;
};

#endif // FPSCAMERA_H
