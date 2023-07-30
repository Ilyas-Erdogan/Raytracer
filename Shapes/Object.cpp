#include "Object.h"
#include "../Intersection.h"

Object::Object()
{
}

Object::Object(const Object& copyObject)
{
}

Object::~Object()
{
}

Object& Object::operator=(const Object& other)
{
	*this = other;
	return *this;
}

bool Object::operator==(const Object& rhs) const
{
	return (this == &rhs);
}

bool Object::operator!=(const Object& rhs) const
{
	return !(*this == rhs);
}

std::vector<Intersection> Object::getIntersections(const std::vector<Intersection>& intersections) const
{
	return std::vector<Intersection>(intersections);
}
