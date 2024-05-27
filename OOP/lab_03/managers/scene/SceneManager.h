#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>

#include <BaseManager.h>

#include "Scene.h"

class SceneManager : public BaseManager
{
public:
    SceneManager();
    ~SceneManager() override = default;
    SceneManager(const SceneManager &) = delete;
    SceneManager &operator=(const SceneManager &) = delete;

    std::shared_ptr<Scene> getScene() const;
    void setScene(const std::shared_ptr<Scene> &scene);

    std::shared_ptr<BaseObject> getObject(int objId);
    bool removeObject(int objId);
    int addObject(const std::shared_ptr<BaseObject> &object);

private:
    std::shared_ptr<Scene> scene_;
};

#endif // SCENEMANAGER_H
