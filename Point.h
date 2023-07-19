#pragma once
#include "Tuple.h"

class Point :
    public Tuple
{
public:
    // Constructors
    Point(const double xCoordinate, const double yCoordinate, const double zCoordinate);
    Point(const Tuple& tup);
    ~Point();
};

