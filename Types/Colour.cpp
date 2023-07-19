#include "Colour.h"

Colour::Colour(const double red, const double green, const double blue)
	: Tuple(red, green, blue, 0)
{
}

Colour::~Colour()
{
}

/**
* Calculates Hadamard/Schur product of two colours
*
* @param lhs left-hand side of expression
* @param rhs reference to right-hand side of expression
*
* @return
*/
Colour Colour::operator*=(const Colour& rhs)
{
	this->x *= rhs.getRed();
	this->y *= rhs.getGreen();
	this->z *= rhs.getBlue();

	return *this;
}

Colour operator*(Colour lhs, const Colour& rhs)
{
	lhs *= rhs;

	return lhs;
}

Colour Colour::operator*=(const double value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;

	return *this;
}

Colour operator*(Colour& lhs, const double value)
{
	lhs *= value;

	return lhs;
}

Colour operator*(const double value, Colour& rhs)
{
	return rhs * value;
}

/**
* Returns red value from calling object.
*
* @return Red value.
*/
double Colour::getRed() const
{
	return this->getX();
}

/**
* Returns green value from calling object.
*
* @return Green value.
*/
double Colour::getGreen() const
{
	return this->getY();
}

/**
* Returns blue value from calling object.
*
* @return Blue value.
*/
double Colour::getBlue() const
{
	return this->getZ();
}
