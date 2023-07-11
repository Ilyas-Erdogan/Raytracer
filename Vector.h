#pragma once
#include "Tuple.h"

class Vector :
    public Tuple
{
public:
    // Constructors
    Vector(double xCoordinate, double yCoordinate, double zCoordinate);
    Vector(const Tuple& tup);
    ~Vector();
};

