#ifndef MODELDIRECTORFACTORY_H
#define MODELDIRECTORFACTORY_H

#include "ModelDirector.h"


class ModelDirectorFactory
{
public:
   virtual ~ModelDirectorFactory() = default;
   virtual std::unique_ptr<ModelDirector> create() = 0;
};


#endif // MODELDIRECTORFACTORY_H
