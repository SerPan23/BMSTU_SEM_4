#ifndef BASECAMERA_H
#define BASECAMERA_H

#include <InVisibleObject.h>

class BaseCamera : public InVisibleObject
{
public:
    BaseCamera() = default;
    explicit BaseCamera(const Vertex &pos) : position_(pos) { }
    ~BaseCamera() override = default;

    virtual Vertex getCenter() override { return position_; };
protected:
    Vertex position_;
};

#endif // BASECAMERA_H
