#include "Intersection.h" 
#include "Shapes/Object.h"

Intersection::Intersection(const double tValue, const std::shared_ptr<Object>& initObject)
	: t {tValue}, object {initObject}
{
}

Intersection::Intersection(const Intersection& copyIntersection)
	: t {copyIntersection.t}, object {copyIntersection.object}
{
}

Intersection::~Intersection()
{
}

Intersection& Intersection::operator=(const Intersection& other)
{
	// Self-assignment guard
	if (this == &other)
	{
		return *this;
	}

	this->t = other.t;
	this->object = other.object;

	return *this;
}

/**
* Checks the equality between two intersection objects.
* 
* @param Intersection rhs Reference to the right-hand side of the comparison.
* 
* @return True if both t values are equal and if both object's point to the same object in memory, otherwise false.
*/
bool Intersection::operator==(const Intersection& rhs) const
{
	bool tCompare = (this->t == rhs.t);
	bool objectCompare = (this->object == rhs.object);

	if (tCompare && objectCompare)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* Checks the equality between two intersection objects.
*
* @param Intersection rhs Reference to the right-hand side of the comparison.
*
* @return True if either t values are not equal and/or if both object's point to the same object in memory, otherwise false.
*/
bool Intersection::operator!=(const Intersection& rhs) const
{
	return !(*this == rhs);
}

/**
* Compares two intersections via their t values.
* 
* @param Intersection rhs Reference to the right-hand side of the comparison.
* 
* @return True if the calling Intersection's t value is less than that of the right-hand side t value, otherwise false.
*/
bool Intersection::operator<(const Intersection& rhs) const
{
	return (this->t < rhs.t);
}

/**
* @return The calling object's t value.
*/
double Intersection::getT() const
{
	return this->t;
}

/**
* @return A immutable reference to the calling object's object.
*/
 std::shared_ptr<Object> Intersection::getObject() const
{
	return std::shared_ptr<Object>(this->object);
}
