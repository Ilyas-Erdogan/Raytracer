#include "Triangle.h"
#include "../Types/Intersection.h"

Triangle::Triangle(const Point& pointOne, const Point& pointTwo, const Point& pointThree)
    : Object(), p1{ pointOne }, p2{pointTwo}, p3{pointThree}, e1{p2 - p1}, e2{p3 - p1}, normal{e2.crossProduct(e1).normalizeVector()}
{
}

Triangle::~Triangle()
{
    Object::~Object();
}

std::shared_ptr<class Triangle> Triangle::toTriangle()
{
    return shared_from_this();
}

/**
* Finds all the intersections by employing the Möller–Trumbore algorithm.
* A ray that misses a triangle should not add any intersections to the vector of intersections.
* A ray that strike a trinagle should add exactly one intersection to the list.
* 
* @param Ray localRay An immutable reference to the ray in local space.
* 
* @return A list of all the intersections.
*/
const std::vector<class Intersection> Triangle::localIntersect(const Ray& localRay)
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
    if (u < EPSILON || u > 1)
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
    return {Intersection(t, shared_from_this())};
}

/**
* @param Point localPoint An immutable reference to the point in local space.
* 
* @return An immutable vector object of the normal of the triangle.
*/
const Vector Triangle::localNormalAt(const class Point& localPoint, const Intersection& hit) const
{
    return this->normal;
}

/**
* @return An immutable reference to the first point in the triangle.
*/
const Point& Triangle::getPointOne() const
{
    return this->p1;
}

/**
* @return An immutable reference to the second point in the triangle.
*/
const Point& Triangle::getPointTwo() const
{
    return this->p2;
}

/**
* @return An immutable reference to the third point in the triangle.
*/
const Point& Triangle::getPointThree() const
{
    return this->p3;
}

/**
* @return An immutable reference to the first edge in the triangle.
*/
const Vector& Triangle::getEdgeOne() const
{
    return this->e1;
}

/**
* @return An immutable reference to the second edge in the triangle.
*/
const Vector& Triangle::getEdgeTwo() const
{
    return this->e2;
}

/**
* @return An immutable reference to the normal of the triangle.
*/
const Vector& Triangle::getNormal() const
{
    return this->normal;
}
