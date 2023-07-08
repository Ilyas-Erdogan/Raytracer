#pragma once
#include "Tuple.h"

class Colour :
    public Tuple
{
public:
    // Constructors
    Colour(double red, double green, double blue);
    ~Colour();

    // Overloaded Operators
    Colour operator*=(const Colour& rhs);
    friend Colour operator*(Colour lhs, const Colour& rhs);

    // Getters
    double getRed() const;
    double getGreen() const;
    double GetBlue() const;
};

