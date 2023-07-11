#pragma once
#include "Tuple.h"

class Point :
    public Tuple
{
public:
    // Constructors
    Point(double xCoordinate, double yCoordinate, double zCoordinate);
    Point(const Tuple& tup);
    ~Point();
};

