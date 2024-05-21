#include "SceneGroup.h"

void SceneGroup::accept(BaseVisitor& v)
{
    v.visit(*this);
}
