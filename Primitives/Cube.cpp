#include "Cube.h"
#include "../Types/Intersection.h"
#include <utility>
#include <limits>

Cube::Cube()
	: Object()
{
}

Cube::~Cube()
{
	Object::~Object();
}

/**
* Identifies intersections on any face.
* 
* @param Ray localRay Immutable reference to the localRay to intersect with the object.
* 
* @return Vector of all the intersections with the cube.
*/
const std::vector<Intersection> Cube::localIntersect(const Ray& localRay)
{
	// Check where the ray intersects each corresponding plane
	std::pair<double, double> xt = this->checkAxis(localRay.getOrigin().getX(), localRay.getDirection().getX());
	std::pair<double, double> yt = this->checkAxis(localRay.getOrigin().getY(), localRay.getDirection().getY());
	std::pair<double, double> zt = this->checkAxis(localRay.getOrigin().getZ(), localRay.getDirection().getZ());

	// Find largest minimum of t values
	double tmin = std::max(xt.first, std::max(yt.first, zt.first));
	// Find smallest of the maximum t values
	double tmax = std::min(xt.second, std::min(yt.second, zt.second));

	// If the minimum t is farther from the ray's origin than the maximum t, then the cube has been missed~
	if (tmin > tmax)
	{
		return {};
	}

	return { Intersection(tmin, shared_from_this()), Intersection(tmax, shared_from_this()) };
}

/**
* Determines the normal of a cube interesected by a ray.
* 
* @param Point localPoint An immutable reference to the point of a ray.
* 
* @return An immutable Vector of the normal at the given point.
*/
const Vector Cube::localNormalAt(const Point& localPoint) const
{
	// Find ray component with largest absolute value
	double maxC = std::max(std::abs(localPoint.getX()), std::max(std::abs(localPoint.getY()), std::abs(localPoint.getZ())));

	// Match face normal to maximum component
	if (maxC == std::abs(localPoint.getX()))
	{
		return Vector(localPoint.getX(), 0, 0);
	}
	else if (maxC == std::abs(localPoint.getY()))
	{
		return Vector(0, localPoint.getY(), 0);
	}

	return Vector(0, 0, localPoint.getZ());
}

/**
* Finds the minimum and maximum t values.
* 
* @param double origin Origin value given by a ray's origin.
* @param double direction Driection value given by a ray's direction.
* 
* @return A pair of the minimum and maximum t intersections
*/
const std::pair<double, double> Cube::checkAxis(const double origin, const double direction)
{
	double tminNumerator = -1 - origin;
	double tmaxNumerator = 1 - origin;

	double tmin, tmax;
	if (std::abs(direction) >= EPSILON)
	{
		tmin = tminNumerator / direction;
		tmax = tmaxNumerator / direction;
	}
	else
	{
		tmin = tminNumerator * std::numeric_limits<double>::infinity();
		tmax = tmaxNumerator * std::numeric_limits<double>::infinity();
	}


	if (tmin > tmax)
	{
		std::swap(tmin, tmax);
	}

	return std::pair<double, double>(tmin, tmax);
}


