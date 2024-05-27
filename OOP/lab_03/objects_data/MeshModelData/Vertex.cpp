#include "Vertex.h"

Vertex::Vertex(const double x, const double y, const double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

Vertex::Vertex(const Vertex &&vertex) noexcept
{
    setX(vertex.x_);
    setY(vertex.y_);
    setZ(vertex.z_);

    vertex.~Vertex();
}

Vertex &Vertex::operator=(Vertex &&vertex) noexcept
{
    setX(vertex.x_);
    setY(vertex.y_);
    setZ(vertex.z_);

    vertex.~Vertex();

    return *this;
}

double Vertex::getX() const
{
    return x_;
}
double Vertex::getY() const
{
    return y_;
}
double Vertex::getZ() const
{
    return z_;
}

void Vertex::setX(double const x)
{
    x_ = x;
}

void Vertex::setY(double const y)
{
    y_ = y;
}

void Vertex::setZ(double const z)
{
    z_ = z;
}

bool Vertex::operator==(const Vertex &vertex) const noexcept
{
    return (vertex.x_ == x_) && (vertex.y_ == y_) && (vertex.z_ == z_);
}
bool Vertex::isEqual(const Vertex &vertex) const noexcept
{
    return *this == vertex;
}

bool Vertex::operator!=(const Vertex &vertex) const noexcept
{
    return !(*this == vertex);
}
bool Vertex::isNotEqual(const Vertex &vertex) const noexcept
{
    return !(*this == vertex);
}

Vertex Vertex::operator+(const Vertex &vertex)  const
{
    Vertex v{*this};

    v.setX(v.x_ + vertex.x_);
    v.setY(v.y_ + vertex.y_);
    v.setZ(v.z_ + vertex.z_);

    return v;
}
Vertex Vertex::operator-(const Vertex &vertex)  const
{
    Vertex v{*this};

    v.setX(v.x_ - vertex.x_);
    v.setY(v.y_ - vertex.y_);
    v.setZ(v.z_ - vertex.z_);

    return v;
}

Vertex Vertex::getAbsVertex(const Vertex &center)
{
    return (*this) + center;
}

Vertex Vertex::getCenter() const
{
    return *this;
}
