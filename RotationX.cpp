#include "RotationX.h"
#include <cmath>

/**
* Constructs a Rotation object for the x axis.
* 
* @param double r Rotation value to be used on the x axis (represented in radians).
*/
RotationX::RotationX(const double r)
	: Matrix({ {1, 0, 0, 0}, {0, std::cos(r), -std::sin(r), 0}, {0, std::sin(r), std::cos(r), 0}, {0, 0, 0, 1}})
{
}

/**
* Constructor an x Rotation object with the provided matrix parameter,.
*
* @param matrix Reference to the matrix object to be copied.
*/
RotationX::RotationX(const Matrix& matrix)
	: Matrix(matrix)
{
}

RotationX::~RotationX()
{
}
