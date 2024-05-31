#ifndef BASEVISITOR_H
#define BASEVISITOR_H

class Scene;
class ObjectComposite;
class MeshModel;
class LightSource;
class BaseCamera;

class BaseVisitor
{
public:
    virtual void visit(Scene &scene) = 0;
    virtual void visit(ObjectComposite& group) = 0;
    virtual void visit(MeshModel &model) = 0;
    virtual void visit(LightSource &light) = 0;
    virtual void visit(BaseCamera &camera) = 0;
};

class Visitable
{
public:
    virtual void accept(BaseVisitor &visitor) = 0;
};

#endif // BASEVISITOR_H
