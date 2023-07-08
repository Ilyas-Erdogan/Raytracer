#include "Colour.h"

Colour::Colour(double red, double green, double blue)
	: Tuple(red, green, blue, 0)
{
}

Colour::~Colour()
{
}

Colour Colour::operator*=(const Colour& rhs)
{
	this->x *= rhs.getRed();
	this->y *= rhs.getGreen();
	this->z *= rhs.GetBlue();

	return *this;
}
/**
* Calculates Hadamard/Schur product of two colours
* 
* @param lhs left-hand side of expression
* @param rhs reference to right-hand side of expression
* 
* @return
*/
Colour operator*(Colour lhs, const Colour& rhs)
{
	lhs *= rhs;

	return lhs;
}

/**
* Returns red value from calling object.
*
* @return red value.
*/
double Colour::getRed() const
{
	return this->getX();
}

/**
* Returns green value from calling object.
*
* @return green value.
*/
double Colour::getGreen() const
{
	return this->getY();
}

/**
* Returns blue value from calling object.
*
* @return blue value.
*/
double Colour::GetBlue() const
{
	return this->getZ();
}
