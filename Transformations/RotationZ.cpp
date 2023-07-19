#include "RotationZ.h"
#include <cmath>

/**
* Constructs a Rotation object for the z axis.
*
* @param double r Rotation value to be used on the z axis (represented in radians).
*/
RotationZ::RotationZ(const double r)
	: Matrix({ {std::cos(r), -std::sin(r), 0, 0}, {std::sin(r), std::cos(r), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}})
{
}

/**
* Constructor an z Rotation object with the provided matrix parameter,.
*
* @param matrix Reference to the matrix object to be copied.
*/
RotationZ::RotationZ(const Matrix& matrix)
	: Matrix(matrix)
{
}

RotationZ::~RotationZ()
{
}
