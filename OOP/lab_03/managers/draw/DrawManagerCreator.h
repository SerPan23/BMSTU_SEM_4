#ifndef DRAWMANAGERCREATOR_H
#define DRAWMANAGERCREATOR_H

#include "DrawManager.h"

class DrawManagerCreator
{
public:
    std::shared_ptr<DrawManager> get();
private:
    void create();
    std::shared_ptr<DrawManager> singleton;
};

#endif // DRAWMANAGERCREATOR_H
