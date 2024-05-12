#ifndef LOADMANAGERCREATOR_H
#define LOADMANAGERCREATOR_H

#include "LoadManager.h"

class LoadManagerCreator
{
public:
    std::shared_ptr<LoadManager> get();
private:
    void create();
    std::shared_ptr<LoadManager> singleton;
};

#endif // LOADMANAGERCREATOR_H
