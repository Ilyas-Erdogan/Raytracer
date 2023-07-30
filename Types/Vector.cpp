#include "Vector.h"
#include <cstdlib>

Vector::Vector(const double xCoordinate, const double yCoordinate, const double zCoordinate)
	: Tuple(xCoordinate, yCoordinate, zCoordinate, 0.0)
{
}

Vector::Vector(const Tuple& tup)
	: Vector(tup.getX(), tup.getY(), tup.getZ())
{
}

Vector::~Vector()
{
	Tuple::~Tuple();
}

/**
* Calculates the reflection vector.
* 
* @param Vector normal Reference to the normal Vector to be multiplied by the calling Vector.
* 
* @return The reflected vector.
*/
Vector Vector::reflect(const Vector& normal) const
{
	return (*this - normal * 2 * this->dotProduct(normal));
}
