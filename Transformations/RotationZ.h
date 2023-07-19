#pragma once
#include "../Types/Matrix.h"
class RotationZ :
    public Matrix
{
public:
    RotationZ(const double r);
    RotationZ(const Matrix& matrix);
    ~RotationZ();
};

