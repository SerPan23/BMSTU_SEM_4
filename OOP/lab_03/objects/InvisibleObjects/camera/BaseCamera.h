#ifndef BASECAMERA_H
#define BASECAMERA_H

#include <InVisibleObject.h>

class BaseCamera : public InVisibleObject
{
public:
    virtual void rotate(float x_offset, float y_offset) = 0;

protected:
    friend class DrawVisitor;
    virtual Matrix4 getViewMatrix() const = 0;
    virtual Matrix4 getProjectionMatrix()  const = 0;
};

#endif // BASECAMERA_H
