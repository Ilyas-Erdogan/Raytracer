#include "SmoothTriangle.h"
#include "../Types/Intersection.h"

SmoothTriangle::SmoothTriangle(const Point& pointOne, const Point& pointTwo, const Point& pointThree, const Vector& normalOne, const Vector& normalTwo, const Vector& normalThree)
	: Object(), p1{pointOne}, p2{pointTwo}, p3{pointThree}, n1{normalOne}, n2{normalTwo}, n3{normalThree}, e1{ p2 - p1 }, e2{ p3 - p1 }
{
}

SmoothTriangle::~SmoothTriangle()
{
	Object::~Object();
}

const std::vector<class Intersection> SmoothTriangle::localIntersect(const Ray& localRay)
{
    // Get cross product of ray's direction with second edge.
    Tuple dirCrossE2 = localRay.getDirection().crossProduct(this->e2);
    // Calcualte the determinant
    double det = this->e1.dotProduct(dirCrossE2);
    // If the determinant's scalar value is equal to 0, there are no intersections.
    if (std::abs(det) < EPSILON)
    {
        return {};
    }

    double f = 1.0 / det;
    Tuple p1ToOrigin = localRay.getOrigin() - this->p1;
    double u = f * p1ToOrigin.dotProduct(dirCrossE2);

    // If the u value isn't between 0 & 1 inclusive, then the ray misses and there are no intersections.
    if (u < 0 || u > 1)
    {
        return {};
    }

    // Get the cross product between the Vector from the first point to origin by the first edge.
    Tuple originCrosseE1 = p1ToOrigin.crossProduct(this->e1);
    double v = f * localRay.getDirection().dotProduct(originCrosseE1);

    // The ray misses, then there are no intersections.
    if (v < 0 || (u + v) > 1)
    {
        return {};
    }

    // Produce an intersection
    double t = f * this->e2.dotProduct(originCrosseE1);
    return { Intersection(t, shared_from_this(), u, v) };
}

const Vector SmoothTriangle::localNormalAt(const Point& localPoint, const Intersection& hit) const
{
	return this->n2 * hit.getU() + this->n3 * hit.getV() + this->n1 * (1 - hit.getU() - hit.getV());
}

std::shared_ptr<SmoothTriangle> SmoothTriangle::toSmoothTriangle()
{
    return shared_from_this();
}

const Point& SmoothTriangle::getPointOne() const
{
	return this->p1;
}

const Point& SmoothTriangle::getPointTwo() const
{
	return this->p2;
}

const Point& SmoothTriangle::getPointThree() const
{
	return this->p3;
}

const Vector& SmoothTriangle::getNormalOne() const
{
	return this->n1;
}

const Vector& SmoothTriangle::getNormalTwo() const
{
	return this->n2;
}

const Vector& SmoothTriangle::getNormalThree() const
{
	return this->n3;
}

const Vector& SmoothTriangle::getEdgeOne() const
{
    return this->e1;
}

const Vector& SmoothTriangle::getEdgeTwo() const
{
    return this->e2;
}
