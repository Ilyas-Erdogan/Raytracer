#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>
#include <algorithm>

/**
* Constructs a sphere object with a default transform matrix represented by a 4 x 4 identity matrix.
*/
Sphere::Sphere()
	: Object(), transform{ Matrix(4, 4).getIdentityMatrix()}
{
}

/**
* Constructs a sphere object with a custom transformation.
* 
* @param Matrix transformMatrix Reference to the transformation matrix to be assigned to the Sphere.
*/
Sphere::Sphere(const Matrix& transformMatrix)
	: Object(), transform{transformMatrix}
{
}

/**
* Constructs a sphere object from another sphere object.
* 
* @param Sphere copySphere Reference to the sphere to be copied.
*/
Sphere::Sphere(const Sphere& copySphere)
	: Object(), transform{copySphere.transform}
{
}

/**
* Constructs a sphere object from an existing base object.
*
* @param Sphere copyObject Reference to the base object to be copied.
*/
Sphere::Sphere(const Object& copyObject)
	: Object(copyObject), transform{Matrix(4, 4).getIdentityMatrix()}
{

}

Sphere::~Sphere()
{
	Object::~Object();
}

/**
* Returns a collection of Intersections.
* The functions calculates discrimant value using Joachimsthal's quadratic equation and uses its value to determine the number of solutions.
*
* @param Ray ray Reference to the ray to be checked whether or not it intersects with the sphere.
*
* @return A vector of all solutions of the equations for discriminants bigger or equal to zero and the sphere that is intersected, otherwise an empty vector.
*/
std::vector<Intersection> Sphere::intersect(const Ray& ray)
{
	// Create new ray transformed by inverse of sphere's transform matrix
	Matrix inverseTransform = this->getTransform().getInverse();
	Ray transformedRay = ray.transform(inverseTransform);

	Vector sphereToRay = transformedRay.getOrigin() - Point(0, 0, 0);

	double a = transformedRay.getDirection().dotProduct(transformedRay.getDirection());
	double b = 2.0 * transformedRay.getDirection().dotProduct(sphereToRay);
	double c = sphereToRay.dotProduct(sphereToRay) - 1.0;

	double discriminant = (b * b) - (4 * a * c);

	std::vector<Intersection> tValues;

	if (discriminant < 0)
	{
		return tValues;
	}
	else
	{
		double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
		double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
		tValues.push_back(Intersection(t1, shared_from_this()));
		tValues.push_back(Intersection(t2, shared_from_this()));
		return tValues;
	}
}

/**
* Returns a hit from a vector of intersections.
* 
* @param vector<Intersection> intersectionVec 
*/
std::unique_ptr<Intersection> Sphere::hit(std::vector<Intersection>& intersectionVec) const
{
	// Early check for empty vector
	if (intersectionVec.empty())
	{
		return nullptr;
	}

	// Sort the vector for iteration optimization
	std::sort(intersectionVec.begin(), intersectionVec.end());
	// Iterate through the vector until first positive result is found
	for ( Intersection& intersection : intersectionVec)
	{
		if (intersection.getT() > 0.0)
		{
			std::unique_ptr<Intersection> returnIntersection(new Intersection(intersection));
			return returnIntersection;
		}
	}

	return nullptr;
}

/**
* @return An immutable reference to the current transformation of the Sphere.
*/
const Matrix& Sphere::getTransform() const
{
	return this->transform;
}

/**
* Sets the calling sphere's transformation matrix.
* 
* @param Matrix transformMatrix Reference to the matrix to be associated with the Sphere.
*/
void Sphere::setTransform(const Matrix& transformMatrix)
{
	this->transform = transformMatrix;
}
