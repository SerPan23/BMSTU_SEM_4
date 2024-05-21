#ifndef SCENEGROUP_H
#define SCENEGROUP_H

#include "ObjectComposite.h"

class SceneGroup : public ObjectComposite
{
public:
    SceneGroup() = default;

    virtual void accept(BaseVisitor& v) override;
};

#endif // SCENEGROUP_H
