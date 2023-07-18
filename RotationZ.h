#pragma once
#include "Matrix.h"
class RotationZ :
    public Matrix
{
public:
    RotationZ(const double r);
    RotationZ(const Matrix& matrix);
    ~RotationZ();
};

