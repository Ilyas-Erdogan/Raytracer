#include "Tuple.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Tuple::Tuple(const double xCoordinate, const double yCoordinate, const double zCoordinate, const double wValue)
	: x{ xCoordinate }, y{ yCoordinate }, z{ zCoordinate }, w{ wValue }
{
}

Tuple::~Tuple()
{
}

Tuple& Tuple::operator=(const Tuple& other)
{
	// Self-assignment guard
	if (this == &other)
	{
		return *this;
	}

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;

	return *this;
}

bool Tuple::operator==(const Tuple& rhs) const
{
	bool validX = std::abs(this->x - rhs.x) < EPSILON;
	bool validY = std::abs(this->y - rhs.y) < EPSILON;
	bool validZ = std::abs(this->z - rhs.z) < EPSILON;
	bool validW = std::abs(this->w - rhs.w) < EPSILON;
	if (validX && validY && validZ && validW)
	{
		return true;
	}

	return false;
}

bool Tuple::operator!=(const Tuple& rhs) const
{
	return !(*this == rhs);
}

Tuple& Tuple::operator+=(const Tuple& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	this->w += rhs.w;

	return *this;
}

Tuple operator+(Tuple lhs, const Tuple& rhs)
{
	lhs += rhs;

	return lhs;
}

Tuple& Tuple::operator-=(const Tuple& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	this->w -= rhs.w;

	return *this;
}

Tuple Tuple::operator-() const
{
	return Tuple(-this->x, -this->y, -this->z, -this->w);
}

Tuple operator-(Tuple lhs, const Tuple& rhs)
{
	lhs -= rhs;

	return lhs;
}

Tuple& Tuple::operator*=(const double value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
	return *this;
}

Tuple operator*(Tuple lhs, const double value)
{
	lhs *= value;

	return lhs;
}

Tuple operator*(const double value, const Tuple& rhs)
{
	return rhs * value;
}

Tuple& Tuple::operator/=(const double value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;

	return *this;
}

Tuple operator/(Tuple lhs, const double value)
{
	lhs /= value;

	return lhs;
}

Tuple operator/(const double value, const Tuple& rhs)
{
	return rhs / value;
}

/**
* Returns X-coordinate from calling object.
* 
* @return X-coordinate/component.
*/
double Tuple::getX() const
{
	return x;
}

/**
* Returns Y-coordinate from calling object.
*
* @return Y-coordinate/component.
*/
double Tuple::getY() const
{
	return y;
}

/**
* Returns Z-coordinate/component from calling object.
*
* @return Z-coordinate/component.
*/
double Tuple::getZ() const
{
	return z;
}

/**
* Returns W value from calling object.
*
* @return W value.
*/
double Tuple::getW() const
{
	return w;
}

/**
* Checks if calling object is a Point.
* 
* @return True when w == 1, otherwise false.
*/
bool Tuple::isPoint() const
{
	return (w == 1.0);
}

/**
* Checks if calling object is a Vector.
*
* @return True when w == 0, otherwise false.
*/
bool Tuple::isVector() const
{
	return (w == 0.0);
}

/**
* Calculates magnitude of calling object.
* 
* @return Magnitude of Vector, otherwise -1.0.
*/
double Tuple::getMagnitude() const
{
	if (isVector())
	{
		return (std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2) + std::pow(this->w, 2)));
	}
	else
	{
		std::cerr << "Object is not a vector. Magnitude unavailable.\n";
		return -1.0;
	}
}

/**
* Modifies calling object into a unit vector.
* 
* @return Void
*/
Tuple Tuple::normalizeVector() const
{
	if (isVector())
	{
		double magnitude = this->getMagnitude();
		return Tuple(this->x / magnitude, this->y / magnitude, this->z / magnitude, this->w);
	}
	else
	{
		std::cerr << "Object is not a vector. Cannot normalize.\n";
	}
}

/**
* ONLY CALL WITH VECTOR OBJECTS.\n
* Calculates dot product of calling object and function parameter.
* 
* @param secondTerm Tuple reference to calculate dot product with.
* @return Result of dot product
*/
double Tuple::dotProduct(const Tuple& secondTerm) const
{
	return ((this->x * secondTerm.x) + (this->y * secondTerm.y) + (this->z * secondTerm.z) + (this->w * secondTerm.w));
}

/**
* ONLY CALL WITH VECTOR OBJECTS
* Calculates cross product of calling object and function parameter.
*
* @param secondTerm Tuple reference to calculate cross product with.
* @return Vector of cross product
*/
Tuple Tuple::crossProduct(const Tuple& secondTerm) const
{
	return Tuple(this->y * secondTerm.z - this->z * secondTerm.y,
		this->z * secondTerm.x - this->x * secondTerm.z,
		this->x * secondTerm.y - this->y * secondTerm.x,
		0
	);
}
