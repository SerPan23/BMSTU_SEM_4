#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <memory>

#include <BaseManager.h>

#include "Vector3.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    ~TransformManager() override = default;
    TransformManager(const TransformManager &) = delete;
    TransformManager &operator=(const TransformManager &) = delete;

    void move(int objectId, const Vector3 &param) const;
    void rotate(int objectId, const Vector3 &param) const;
    void scale(int objectId, const Vector3 &param) const;
};

#endif // TRANSFORMMANAGER_H
