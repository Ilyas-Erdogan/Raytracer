#pragma once
#include "Tuple.h"

class Vector :
    public Tuple
{
public:
    // Constructors
    Vector(const double xCoordinate, const double yCoordinate, const double zCoordinate);
    Vector(const Tuple& tup);
    ~Vector();
};

