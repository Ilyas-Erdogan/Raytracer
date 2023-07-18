#pragma once
#include "Matrix.h"
class RotationY :
    public Matrix
{
public:
    // Constructors
    RotationY(const double r);
    RotationY(const Matrix& matrix);
    ~RotationY();
};

