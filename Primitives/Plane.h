#pragma once
#include "Object.h"

class Plane :
    public Object, public std::enable_shared_from_this<Plane>
{
public:
    Plane();
    ~Plane();

    // Utilities
    virtual const std::vector<Intersection> localIntersect(const Ray& localRay);
    virtual const Vector localNormalAt(const class Point& localPoint) const;
private:
    const double EPSILON{ 0.00001 };
    const Vector normal = Vector(0, 1, 0);
};

