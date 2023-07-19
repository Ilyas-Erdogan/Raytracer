#include "Translation.h"

/**
* Constructs a translation object as an identity matrix with the last column containing transformation coordinates.
* 
* @param x Translation x value.
* @param y Translation y value.
* @param z Translation z value.
*/
Translation::Translation(const double x, const double y, const double z)
	: Matrix({ {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1} })
{
}

/**
* Constructor a translation object with the provided matrix parameter,.
* 
* @param matrix Reference to the matrix object to be copied.
*/
Translation::Translation(const Matrix& matrix)
	: Matrix(matrix)
{
}

Translation::~Translation()
{
}
