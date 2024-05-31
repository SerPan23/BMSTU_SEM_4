#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "BaseObject.h"

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    int addObject(const std::shared_ptr<BaseObject> &obj);
    bool removeObject(const int id);
    std::shared_ptr<BaseObject> getObject(int objectId);

    Iterator begin();
    Iterator end();

    void accept(BaseVisitor& v);

private:
    // std::shared_ptr<SceneGroup> objects_;
    ObjectMap objects_;
    int objCount = 0;
};

#endif // SCENE_H
