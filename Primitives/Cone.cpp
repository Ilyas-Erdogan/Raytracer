#include "Cone.h"
#include "../Types/Intersection.h"
#include <cmath>

Cone::Cone(const double min, const double max, const bool close)
	: Object(), minimum{ min }, maximum{ max }, closed{ close }
{
}

Cone::~Cone()
{
	Object::~Object();
}

/**
* @return The minimum of the cone truncation.
*/
double Cone::getMinimum() const
{
	return this->minimum;
}

/**
* @return The maximum of the cone truncation..
*/
double Cone::getMaximum() const
{
	return this->maximum;
}

/**
* @return If the cone has closed tops or not.
*/
bool Cone::isClosed() const
{
	return this->closed;
}

/**
* Identifies intersections on any face.
*
* @param Ray localRay Immutable reference to the localRay to intersect with the cone.
*
* @return Vector of all the intersections with the cone.
*/
const std::vector<Intersection> Cone::localIntersect(const Ray& localRay)
{
	double a = localRay.getDirection().getX() * localRay.getDirection().getX() - localRay.getDirection().getY() * localRay.getDirection().getY() + localRay.getDirection().getZ() * localRay.getDirection().getZ();
	double b = 2 * localRay.getOrigin().getX() * localRay.getDirection().getX() - 2 * localRay.getOrigin().getY() * localRay.getDirection().getY() + 2 * localRay.getOrigin().getZ() * localRay.getDirection().getZ();
	double c = localRay.getOrigin().getX() * localRay.getOrigin().getX() - localRay.getOrigin().getY() * localRay.getOrigin().getY() + localRay.getOrigin().getZ() * localRay.getOrigin().getZ();

	std::vector<Intersection> xs = {};

	if (std::abs(a) < EPSILON && std::abs(b) > EPSILON)
	{
		double t = -c / (2.0 * b);
		xs.push_back(Intersection(t, shared_from_this()));
		intersectCaps(localRay, xs);
		return xs;
	} 
	else if (std::abs(a) < EPSILON)
	{
		return {};
	}

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
* Determines the normal of a cone interesected by a ray.
*
* @param Point localPoint An immutable reference to the point of a ray.
*
* @return An immutable Vector of the normal at the given point.
*/
const Vector Cone::localNormalAt(const Point& localPoint) const
{
	double dist = localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ();

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
		double y = std::sqrt(localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ());
		if (localPoint.getY() > 0.0)
		{
			y = -y;
		}
		return Vector(localPoint.getX(), y, localPoint.getZ());
	}
}

/**
* Checks to see if the given ray intersects the end caps of the called cone.
*
* @param Ray ray An immutable reference to the ray.
* @param std::vector<Intersection> xs A reference to the list of intersectoins.
*/
void Cone::intersectCaps(const Ray& ray, std::vector<Intersection>& xs)
{
	if (!this->closed || std::abs(ray.getDirection().getY()) < EPSILON)
	{
		return;
	}

	double t = (this->minimum - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (this->checkCap(ray, t, std::abs(this->minimum)))
	{
		xs.push_back(Intersection(t, shared_from_this()));
	}

	t = (this->maximum - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (this->checkCap(ray, t, std::abs(this->maximum)))
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
* @param double capRadius The radius of the cap on the cone.
*
* @return True if the point of intersection lies within the radius of the cylinder, otherwise false.
*/
const bool Cone::checkCap(const Ray& ray, const double t, const double capRadius) const
{
	double x = ray.getOrigin().getX() + t * ray.getDirection().getX();
	double z = ray.getOrigin().getZ() + t * ray.getDirection().getZ();

	return ((x * x) + (z * z)) <= capRadius + EPSILON;
}
