#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "SceneGroup.h"
#include "BaseObject.h"

class Scene
{
public:
    Scene();
    ~Scene() = default;

    bool addObject(std::shared_ptr<BaseObject> &obj);
    bool removeObject(const Iterator &);
    std::shared_ptr<SceneGroup> getVisibleObjects();
    std::shared_ptr<SceneGroup> getInVisibleObjects();
    void accept(BaseVisitor& v);

private:
    std::shared_ptr<SceneGroup> visibleObjects_;
    std::shared_ptr<SceneGroup> inVisibleObjects_;
};

#endif // SCENE_H
