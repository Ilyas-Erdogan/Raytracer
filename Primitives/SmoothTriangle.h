#pragma once
#include "Object.h"

class SmoothTriangle :
    public Object, public std::enable_shared_from_this<SmoothTriangle>
{
public:
    SmoothTriangle(const Point& pointOne, const Point& pointTwo, const Point& pointThree, const Vector& normalOne, const Vector& normalTwo, const Vector& normalThree);
    ~SmoothTriangle();

    virtual const std::vector<class Intersection> localIntersect(const Ray& localRay);
    virtual const Vector localNormalAt(const class Point& localPoint, const Intersection& hit) const;
    std::shared_ptr<SmoothTriangle> toSmoothTriangle() override;

    // Getters
    const Point& getPointOne() const;
    const Point& getPointTwo() const;
    const Point& getPointThree() const;
    const Vector& getNormalOne() const;
    const Vector& getNormalTwo() const;
    const Vector& getNormalThree() const;
    const Vector& getEdgeOne() const;
    const Vector& getEdgeTwo() const;
private:
    const double EPSILON{ 0.00001 };
    Point p1;
    Point p2;
    Point p3;
    Vector n1;
    Vector n2;
    Vector n3;
    Vector e1;
    Vector e2;
};

