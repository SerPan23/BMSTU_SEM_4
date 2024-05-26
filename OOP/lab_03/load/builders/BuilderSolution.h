#ifndef BUILDERSOLUTION_H
#define BUILDERSOLUTION_H

#include <memory>

#include "ModelBuilder.h"


class BuilderSolution
{
public:
    BuilderSolution() = default;

    static std::shared_ptr<ModelBuilder> create(const std::string &path, std::shared_ptr<ModelSource> source);
};

#endif // BUILDERSOLUTION_H
