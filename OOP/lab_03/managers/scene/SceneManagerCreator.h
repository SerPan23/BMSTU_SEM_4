#ifndef SCENEMANAGERCREATOR_H
#define SCENEMANAGERCREATOR_H

#include "SceneManager.h"

class SceneManagerCreator
{
public:
    std::shared_ptr<SceneManager> get();
private:
    void create();
    std::shared_ptr<SceneManager> singleton;
};

#endif // SCENEMANAGERCREATOR_H
