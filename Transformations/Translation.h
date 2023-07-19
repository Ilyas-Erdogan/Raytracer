#pragma once
#include "../Types/Matrix.h"

class Translation
	: public Matrix
{
public:
	// Constructors
	Translation(const double x, const double y, const double z);
	Translation(const Matrix& matrix);
	~Translation();
};

