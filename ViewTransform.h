#pragma once
#include "Types/Matrix.h"
#include "Types/Point.h"
#include "Types/Vector.h"

class ViewTransform :
    public Matrix
{
public:
    ViewTransform(const Point& fromPoint, const Point& toPoint, const Vector& upVector);
    ViewTransform(const ViewTransform& copyTransform);
    ~ViewTransform();
private:
    Point from;
    Point to;
    Vector up;
};

