#include "Point.h"
#include <cstdlib>

Point::Point(double xCoordinate, double yCoordinate, double zCoordinate)
	:Tuple(xCoordinate, yCoordinate, zCoordinate, 1.0)
{
}

Point::Point(const Tuple& tup)
	: Tuple(tup.getX(), tup.getY(), tup.getZ())
{
}

Point::~Point()
{
	Tuple::~Tuple();
}

