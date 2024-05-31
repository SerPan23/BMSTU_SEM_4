#ifndef ADJACENCYLISTSOURCEFACTORY_H
#define ADJACENCYLISTSOURCEFACTORY_H

#include "ModelSourceFactory.h"

class AdjacencyListSourceFactory : public ModelSourceFactory
{
public:
    virtual std::shared_ptr<ModelSource> create(const std::string &path) override;
};

#endif // ADJACENCYLISTSOURCEFACTORY_H
