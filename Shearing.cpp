#include "Shearing.h"

/**
* Consructs a shearing object to be applied to another type.
* 
* @param double x_y Transform x in proportion to y.
* @param double x_z Transform x in proportion to z.
* @param double y_x Transform y in proportion to x.
* @param double y_z Transform y in proportion to z.
* @param double z_x Transform z in proportion to x.
* @param double z_y Transform z in proportion to y.
*/
Shearing::Shearing(const double x_y, const double x_z, const double y_x, const double y_z, const double z_x, const double z_y)
	: Matrix({ {1, x_y, x_z, 0}, {y_x, 1, y_z, 0}, {z_x, z_y, 1, 0}, {0, 0, 0, 1} })
{
}

/**
* Constructs a shearing object passed on provided matrix.
* 
* @param Matrix matrix Reference to matrix to be copied to calling object.
*/
Shearing::Shearing(const Matrix& matrix)
	: Matrix(matrix)
{
}

Shearing::~Shearing()
{
}
