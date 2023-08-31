#pragma once
#include "Object.h"

class Cylinder :
    public Object, public std::enable_shared_from_this<Cylinder>
{
public:
    Cylinder(const double min = -std::numeric_limits<double>::infinity(), const double max = std::numeric_limits<double>::infinity(), const bool close = false);
    ~Cylinder();

    // Getters
    double getMinimum() const;
    double getMaximum() const;
    bool isClosed() const;

    // Utilities
    virtual const std::vector<Intersection> localIntersect(const class Ray& localRay);
    virtual const Vector localNormalAt(const class Point& localPoint, const Intersection& hit) const;
    void intersectCaps(const Ray& ray, std::vector<Intersection>& xs);
    const bool checkCap(const Ray& ray, const double t) const;

private:
    const double EPSILON{ 0.00001 };
    double minimum;
    double maximum;
    bool closed;
};

