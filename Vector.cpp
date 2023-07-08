#include "Vector.h"
#include <cstdlib>

Vector::Vector(double xCoordinate, double yCoordinate, double zCoordinate)
	: Tuple(xCoordinate, yCoordinate, zCoordinate, 0.0)
{
}

Vector::~Vector()
{
	Tuple::~Tuple();
}
