#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "Matrix4.h"
#include "glm_wrapper.h"

class Transformer
{
public:
    Transformer() = default;
    virtual ~Transformer() = default;

    virtual Matrix4 transform(const Matrix4& mat) = 0;
};

#endif // TRANSFORMER_H
