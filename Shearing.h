#pragma once
#include "Matrix.h"
class Shearing :
    public Matrix
{
public:
    // Constructors
    Shearing(const double x_y, const double x_z, const double y_x, const double y_z, const double z_x, const double z_y);
    Shearing(const Matrix& matrix);
    ~Shearing();
};

