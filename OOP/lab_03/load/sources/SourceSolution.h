#ifndef SOURCESOLUTION_H
#define SOURCESOLUTION_H

#include <memory>

#include "ModelSource.h"

class SourceSolution
{
public:
    SourceSolution() = default;

    static std::shared_ptr<ModelSource> create(const std::string &path);
};

#endif // SOURCESOLUTION_H
