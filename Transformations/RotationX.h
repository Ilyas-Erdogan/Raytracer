#pragma once
#include "../Types/Matrix.h"
class RotationX :
    public Matrix
{
public:
    // Constructors
    RotationX(const double r);
    RotationX(const Matrix& matrix);
    ~RotationX();
};

