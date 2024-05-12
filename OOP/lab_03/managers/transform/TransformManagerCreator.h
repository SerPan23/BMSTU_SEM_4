#ifndef TRANSFORMMANAGERCREATOR_H
#define TRANSFORMMANAGERCREATOR_H

#include "TransformManager.h"

class TransformManagerCreator
{
public:
    std::shared_ptr<TransformManager> get();
private:
    void create();
    std::shared_ptr<TransformManager> singleton;
};

#endif // TRANSFORMMANAGERCREATOR_H
