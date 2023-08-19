#include "Computation.h"

/**
* Creates computation object containing all necessary data to perform shading.
*
* @param double tVal The t (time) vaue as seen by
* @param shared_ptr<Object> initObject Reference to the object in that was hit
*/
Computation::Computation(const double tVal, std::shared_ptr<Object> initObject, const Point& pointVal, const Vector& eyeVVal, const Vector& normalVVal, const bool insideVal, const Point& overPointVal, const Vector& reflectVVal)
	: t{ tVal }, object{ std::move(initObject) }, point{ pointVal }, eyeV{ eyeVVal }, normalV{ normalVVal }, inside{ insideVal }, overPoint{ overPointVal }, reflectV{ reflectVVal }
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

/**
* @return An immutable reference to the over point.
*/
const Point& Computation::getOverPoint() const
{
	return this->overPoint;
}

/**
* @return True if i
*/
bool Computation::isInside() const
{
	return this->inside;
}

const Vector& Computation::getReflectV() const
{
	return this->reflectV;
}