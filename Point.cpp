#include "Point.h"
#include <cstdlib>

Point::Point(const double xCoordinate, const double yCoordinate, const double zCoordinate)
	:Tuple(xCoordinate, yCoordinate, zCoordinate, 1.0)
{
}

Point::Point(const Tuple& tup)
	: Point(tup.getX(), tup.getY(), tup.getZ())
{
}

Point::~Point()
{
	Tuple::~Tuple();
}

