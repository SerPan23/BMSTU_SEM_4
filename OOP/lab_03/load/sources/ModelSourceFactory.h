#ifndef MODELSOURCEFACTORY_H
#define MODELSOURCEFACTORY_H

#include <memory>
#include <string>

#include "ModelSource.h"

class ModelSourceFactory
{
public:
    virtual ~ModelSourceFactory() = default;
    virtual std::shared_ptr<ModelSource> create(const std::string &path) = 0;
};

#endif // MODELSOURCEFACTORY_H
