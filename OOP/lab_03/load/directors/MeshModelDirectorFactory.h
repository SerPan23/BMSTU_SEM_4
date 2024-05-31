#ifndef MESHMODELDIRECTORFACTORY_H
#define MESHMODELDIRECTORFACTORY_H

#include <ModelDirectorFactory.h>


class MeshModelDirectorFactory : public ModelDirectorFactory
{
public:
    virtual std::unique_ptr<ModelDirector> create() override;
};

#endif // MESHMODELDIRECTORFACTORY_H
