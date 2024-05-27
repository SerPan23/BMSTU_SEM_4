#ifndef SCALETRANSFORMER_H
#define SCALETRANSFORMER_H

#include <Transformer.h>

class ScaleTransformer : public Transformer
{
public:
    ScaleTransformer(const double x, const double y, const double z);
    virtual Matrix4 transform(const Matrix4& mat) override;

private:
    double x_ = 1;
    double y_ = 1;
    double z_ = 1;
};

#endif // SCALETRANSFORMER_H
