#ifndef BASECAMERA_H
#define BASECAMERA_H

#include <InVisibleObject.h>

class BaseCamera : public InVisibleObject
{
public:
    virtual Matrix4 getViewMatrix() const = 0;
    virtual Matrix4 getProjectionMatrix()  const = 0;
};

#endif // BASECAMERA_H
