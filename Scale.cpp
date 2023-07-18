#include "Scale.h"

/**
* Constructs a scaling object as an identity matrix with the first three columns containing one scaling coordinate (x, y, z) respectively.
*
* @param x Scaling x value.
* @param y Scaling y value.
* @param z Scaling z value.
*/
Scale::Scale(const double x, const double y, const double z)
	: Matrix({ {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1} })
{
}

/**
* Constructor a scaling object with the provided matrix parameter,.
*
* @param matrix Reference to the matrix object to be copied.
*/
Scale::Scale(const Matrix& matrix)
	: Matrix(matrix)
{
}

Scale::~Scale()
{
}
