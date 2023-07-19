#include "RotationY.h"
#include <cmath>

/**
* Constructs a Rotation object for the y axis.
*
* @param double r Rotation value to be used on the y axis (represented in radians).
*/
RotationY::RotationY(const double r)
	: Matrix({ {std::cos(r), 0, std::sin(r), 0}, {0, 1, 0, 0}, {-std::sin(r), 0, std::cos(r), 0}, {0, 0, 0, 1}})
{
}

/**
* Constructor an y Rotation object with the provided matrix parameter,.
*
* @param matrix Reference to the matrix object to be copied.
*/
RotationY::RotationY(const Matrix& matrix)
	: Matrix(matrix)
{
}

RotationY::~RotationY()
{
}
