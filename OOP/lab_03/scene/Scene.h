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

    int addObject(const std::shared_ptr<BaseObject> &obj);
    bool removeObject(const Iterator &);
    bool removeObject(const int id);
    std::shared_ptr<BaseObject> getObject(int objectId);

    std::shared_ptr<SceneGroup> getObjects();

    void accept(BaseVisitor& v);

private:
    std::shared_ptr<SceneGroup> objects_;
};

#endif // SCENE_H
