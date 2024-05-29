#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <memory>

#include "Matrix4.h"

#include "MoveTransformer.h"
#include "RotateTransformer.h"
#include "ScaleTransformer.h"


class Transformation
{
public:
    Transformation() = default;

    void operator+=(std::shared_ptr<Transformer> transformer);

    // void operator+=(std::shared_ptr<MoveTransformer> transformer);
    // void operator+=(std::shared_ptr<RotateTransformer> transformer);
    // void operator+=(std::shared_ptr<ScaleTransformer> transformer);

    Matrix4 getMatrix() const;

private:
    Matrix4 moveMatrix_{1.0};
    Matrix4 RotationMatrix_{1.0};
    Matrix4 ScaleMatrix_{1.0};
};

#endif // TRANSFORMATION_H
