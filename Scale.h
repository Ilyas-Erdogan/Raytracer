#pragma once
#include "Matrix.h"
class Scale :
    public Matrix
{
public:
    // Constructors
    Scale(const double x, const double y, const double z);
    Scale(const Matrix& matrix);
    ~Scale();
};

