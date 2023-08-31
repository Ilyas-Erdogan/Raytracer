#include "Cylinder.h"
#include "../Types/Intersection.h"

#include <cmath>
#include <limits>

Cylinder::Cylinder(const double min, const double max, const bool close)
	: Object(), minimum{ min }, maximum{ max }, closed{ close }
{
}

Cylinder::~Cylinder()
{
	Object::~Object();
}

/**
* @return The minimum of the cylinder truncation.
*/
double Cylinder::getMinimum() const
{
	return this->minimum;
}

/**
* @return The maximum of the cylinder truncation.
*/
double Cylinder::getMaximum() const
{
	return this->maximum;
}

/**
* @return If the cylinder has closed tops or not.
*/
bool Cylinder::isClosed() const
{
	return this->closed;
}

/**
* Identifies intersections on any face.
*
* @param Ray localRay Immutable reference to the localRay to intersect with the cylinder.
*
* @return Vector of all the intersections with the cone.
*/
const std::vector<Intersection> Cylinder::localIntersect(const Ray& localRay)
{
	double a = localRay.getDirection().getX() * localRay.getDirection().getX() + localRay.getDirection().getZ() * localRay.getDirection().getZ();
	double b = 2 * localRay.getOrigin().getX() * localRay.getDirection().getX() + 2 * localRay.getOrigin().getZ() * localRay.getDirection().getZ();
	double c = localRay.getOrigin().getX() * localRay.getOrigin().getX() + localRay.getOrigin().getZ() * localRay.getOrigin().getZ() - 1;

	double discriminant = b * b - 4 * a * c;

	// If the ray does not intersect the cylinder, there are no intersections
	if (discriminant < 0.0)
	{
		return {};
	}

	double t0 = (-b - std::sqrt(discriminant)) / (2 * a);
	double t1 = (-b + std::sqrt(discriminant)) / (2 * a);

	if (t0 > t1)
	{
		std::swap(t0, t1);
	}

	double y0 = localRay.getOrigin().getY() + t0 * localRay.getDirection().getY();

	std::vector<Intersection> xs = {};

	if (this->minimum < y0 && y0 < this->maximum)
	{
		xs.push_back(Intersection(t0, shared_from_this()));
	}

	double y1 = localRay.getOrigin().getY() + t1 * localRay.getDirection().getY();

	if (this->minimum < y1 && y1 < this->maximum)
	{
		xs.push_back(Intersection(t1, shared_from_this()));
	}

	intersectCaps(localRay, xs);

	return xs;
}

/**
* Determines the normal of a cylinder interesected by a ray.
*
* @param Point localPoint An immutable reference to the point of a ray.
*
* @return An immutable Vector of the normal at the given point.
*/
const Vector Cylinder::localNormalAt(const class Point& localPoint, const Intersection& hit) const
{
	// Compute the square of the distance from the y-axis
	double dist = localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ();


	// Check to see which cap end the point corresponds to
	if (dist < 1 && localPoint.getY() >= this->maximum - EPSILON)
	{
		return Vector(0, 1, 0);
	}
	else if (dist < 1 && localPoint.getY() <= this->minimum + EPSILON)
	{
		return Vector(0, -1, 0);
	}
	else
	{
		return Vector(localPoint.getX(), 0, localPoint.getZ());
	}
}

/**
* Checks to see if the given ray intersects the end caps of the called cylinder.
* 
* @param Ray ray An immutable reference to the ray.
* @param std::vector<Intersection> xs A reference to the list of intersectoins.
*/
void Cylinder::intersectCaps(const Ray& ray, std::vector<Intersection>& xs)
{
	if (!this->closed || std::abs(ray.getDirection().getY()) < EPSILON)
	{
		return;
	}

	double t = (this->minimum - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (this->checkCap(ray, t))
	{
		xs.push_back(Intersection(t, shared_from_this()));
	}

	t = (this->maximum - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (this->checkCap(ray, t))
	{
		xs.push_back(Intersection(t, shared_from_this()));
	}
}

/**
* Checks to see if the intersection at t is within a radius of 1
* (the radius of your cylinders) from the y axis.
* 
* @param Ray ray An immutable reference to the ray being intersected with the cylinder.
* @param double t An immutable t value of the intersection.
* 
* @return True if the point of intersection lies within the radius of the cylinder, otherwise false.
*/
const bool Cylinder::checkCap(const Ray& ray, const double t) const
{
	double x = ray.getOrigin().getX() + t * ray.getDirection().getX();
	double z = ray.getOrigin().getZ() + t * ray.getDirection().getZ();

	return ((x * x) + (z * z)) <= 1;
}
