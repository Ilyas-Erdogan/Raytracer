#include "Computation.h"
#include <cmath>

/**
* Creates computation object containing all necessary data to perform shading.
*
* @param double tVal The t (time) vaue as seen by
* @param shared_ptr<Object> initObject Reference to the object in that was hit
*/
Computation::Computation(const double tVal,
	std::shared_ptr<class Object> initObject,
	const Point& pointVal,
	const Vector& eyeVVal,
	const Vector& normalVVal,
	const bool insideVal,
	const Point& overPointVal,
	const Point& underPointVal,
	const Vector& reflectVVal,
	const double n1Val,
	const double n2Val)
	: t{ tVal },
	object{ std::move(initObject) },
	point{ pointVal },
	eyeV{ eyeVVal },
	normalV{ normalVVal },
	inside{ insideVal },
	overPoint{ overPointVal },
	underPoint{ underPointVal },
	reflectV{ reflectVVal },
	n1{ n1Val },
	n2{ n2Val }
{
}

Computation::Computation(const Computation& copyComputation)
	: t{ copyComputation.t },
	object{ copyComputation.getObject() },
	point{ copyComputation.point },
	eyeV{ copyComputation.eyeV },
	normalV{ copyComputation.normalV },
	inside{ copyComputation.inside },
	overPoint{ copyComputation.overPoint },
	underPoint{ copyComputation.underPoint },
	reflectV{ copyComputation.reflectV },
	n1{ copyComputation.n1 },
	n2{ copyComputation.n2 }
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
const std::shared_ptr<Object>& Computation::getObject() const
{
	return this->object;
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

/**
* @return The reflection vector of the computation.
*/
const Vector& Computation::getReflectV() const
{
	return this->reflectV;
}

/**
* @return The refractive index belonging to the material being entered (n2)
*/
double Computation::getEnter() const
{
	return this->n2;
}

/**
* @return The refractive index belonging to the material being exited (n1)
*/
double Computation::getExit() const
{
	return this->n1;
}

/**
* @return The point that lies beneath the intersected surface.
*/
const Point& Computation::getUnderPoint() const
{
	return this->underPoint;
}

/**
* Returns a number that represants what fraction of the light is reflected.
* 
* @return A number between 0 and 1 (inclusive).
*/
double Computation::schlick() const
{
	// Find the cosine of the angle between the eye and the normal vectors
	double cos = this->getEyeV().dotProduct(this->getNormalV());

	// Total internal reflection can only ccur is n1 > n2
	if (this->getExit() > this->getEnter())
	{
		double n = this->getExit() / this->getEnter();
		double sin2T = n * n * (1.0 - cos * cos);
		if (sin2T > 1.0)
		{
			return 1.0;
		}
		else
		{
			// Compute cosine of theta t using trig identity
			double cosT = std::sqrt(1.0 - sin2T);
			cos = cosT;
		}
	}

	double r0 = ((this->getExit() - this->getEnter()) / (this->getExit() + this->getEnter()));
	r0 *= r0;

	return r0 + (1 - r0) * std::pow((1 - cos), 5);
}