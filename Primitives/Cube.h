#pragma once
#include "Object.h"

class Cube :
    public Object, public std::enable_shared_from_this<Cube>
{
public:
    Cube();
    ~Cube();

    // Utility
    virtual const std::vector<Intersection> localIntersect(const Ray& localRay);
    virtual const Vector localNormalAt(const class Point& localPoint) const;
    const std::pair<double, double> checkAxis(const double origin, const double direction) ;
private:
    const double EPSILON{ 0.00001 };
};

