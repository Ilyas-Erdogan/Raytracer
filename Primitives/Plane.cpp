#include "Plane.h"

#include "../Types/Intersection.h"
#include <cmath>

Plane::Plane()
{
}

Plane::~Plane()
{
}

/**
* Determines if an intersection occured with the given plane and ray.
* 
* @param Ray localRay The local ray given from the abstract object.
* 
* @return An intersection of a single vector if one is found, otherwise an empty vector.
*/
const std::vector<Intersection> Plane::localIntersect(const Ray& localRay)
{
	// Check for a slope within the ray's direction vector
	if (std::abs(localRay.getDirection().getY()) < EPSILON)
	{
		return {};
	}
	else
	{
		double t = -localRay.getOrigin().getY() / localRay.getDirection().getY();
		return { Intersection(t, shared_from_this()) };
	}
}

/**
* @param Point localPoint The local point given from the abstract object.
* 
* Returns a constant normal in the upwards y direction regardless of the parameter.
*/
const Vector Plane::localNormalAt(const Point& localPoint) const
{
	return this->normal;
}
