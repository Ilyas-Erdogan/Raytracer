#include "Vector.h"
#include <cstdlib>

Vector::Vector(double xCoordinate, double yCoordinate, double zCoordinate)
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
