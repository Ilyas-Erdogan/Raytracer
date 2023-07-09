#pragma once
#include "Tuple.h"

class Colour :
    public Tuple
{
public:
    // Constructors
    Colour(const double red = 0.0, const double green = 0.0, const double blue = 0.0);
    ~Colour();

    // Overloaded Operators
    Colour operator*=(const Colour& rhs);
    friend Colour operator*(Colour lhs, const Colour& rhs);
    Colour operator*=(const double value);
    friend Colour operator*(Colour& lhs, const double value);
    friend Colour operator*(const double value, Colour& rhs);

    // Getters
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
};

