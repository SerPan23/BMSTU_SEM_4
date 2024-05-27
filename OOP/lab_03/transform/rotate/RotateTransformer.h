#ifndef ROTATETRANSFORMER_H
#define ROTATETRANSFORMER_H

#include <Transformer.h>

class RotateTransformer : public Transformer
{
public:
    RotateTransformer(const double x, const double y, const double z);
    virtual Matrix4 transform(const Matrix4& mat) override;

private:
    double x_ = 0;
    double y_ = 0;
    double z_ = 0;
};

#endif // ROTATETRANSFORMER_H
