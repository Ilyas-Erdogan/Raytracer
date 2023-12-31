#include "Sphere.h"
#include "../Ray.h"
#include "../Types/Intersection.h"

#include <cmath>

/**
* Constructs a sphere object with a default transform matrix represented by a 4 x 4 identity matrix.
*/
Sphere::Sphere()
	: Object()
{
}

/**
* Constructs a sphere object with a custom transformation.
* 
* @param Matrix transformMatrix Reference to the transformation matrix to be assigned to the Sphere.
*/
Sphere::Sphere(const Matrix& transformMatrix)
	: Object(transformMatrix)
{
}

/**
* Constructs a sphere object from another sphere object.
* 
* @param Sphere copySphere Reference to the sphere to be copied.
*/
Sphere::Sphere(const Sphere& copySphere)
	: Object(copySphere.getTransform())
{
}

/**
* Constructs a sphere object from an existing base object.
*
* @param Sphere copyObject Reference to the base object to be copied.
*/
Sphere::Sphere(const Object& copyObject)
	: Object(copyObject)
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
* @param Ray localRay Reference to the local ray to be checked whether or not it intersects with the sphere.
*
* @return A vector of all solutions of the equations for discriminants bigger or equal to zero and the sphere that is intersected, otherwise an empty vector.
*/
const std::vector<Intersection> Sphere::localIntersect(const Ray& localRay)
{
	// Create new ray transformed by inverse of sphere's transform matrix
	Vector sphereToRay = localRay.getOrigin() - Point(0, 0, 0);

	double a = localRay.getDirection().dotProduct(localRay.getDirection());
	double b = 2.0 * localRay.getDirection().dotProduct(sphereToRay);
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
* @param Point localPoint The local point given from the abstract object.
*
* @return The local point as a vector.
*/
const Vector Sphere::localNormalAt(const class Point& localPoint, const Intersection& hit) const
{
	return localPoint;
}