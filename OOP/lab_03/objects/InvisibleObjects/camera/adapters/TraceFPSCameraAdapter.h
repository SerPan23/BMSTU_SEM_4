#ifndef TRACEFPSCAMERAADAPTER_H
#define TRACEFPSCAMERAADAPTER_H

#include <memory>

#include "FPSCamera.h"

class TraceFPSCameraAdapter
{
public:
    TraceFPSCameraAdapter(std::shared_ptr<FPSCamera> ad) : adaptee(ad) {}

    void changeTrace(float xOffset, float yOffset);

private:
    std::shared_ptr<FPSCamera> adaptee;
};

#endif // TRACEFPSCAMERAADAPTER_H
