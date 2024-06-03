#ifndef BASECAMERA_H
#define BASECAMERA_H

#include <InVisibleObject.h>

class BaseCamera : public InVisibleObject
{
public:
    BaseCamera() = default;

protected:
    friend class DrawVisitor;
    virtual Matrix4 getViewMatrix() = 0;
    virtual Matrix4 getProjectionMatrix()  const = 0;
};

#endif // BASECAMERA_H
