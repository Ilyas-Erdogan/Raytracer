#include "Computation.h"

Computation::Computation(const double tVal, const std::shared_ptr<Object>& initObject, const Point& pointVal, const Vector& eyeVVal, const Vector& normalVVal, const bool insideVal)
	: t{ tVal }, object{ initObject }, point { pointVal }, eyeV{ eyeVVal }, normalV{ normalVVal }, inside{ insideVal }
{
}

Computation::~Computation()
{
}

/**
* @return The t value of the computation.
*/
double Computation::getT() const
{
	return this->t;
}

/**
* @return An immutable shared pointer to the object of the computation.
*/
const std::shared_ptr<Object> Computation::getObject() const
{
	return std::shared_ptr<Object>(this->object);
}

/**
* @return An immutable reference to the point of the computation.
*/
const Point& Computation::getPoint() const
{
	return this->point;
}

/**
* @return An immutable reference to the eye vector of the computation.
*/
const Vector& Computation::getEyeV() const
{
	return this->eyeV;
}

/**
* @return An immutable reference to the normal vector of the computation.
*/
const Vector& Computation::getNormalV() const
{
	return this->normalV;
}

bool Computation::isInside() const
{
	return this->inside;
}
