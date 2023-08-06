#pragma once
#include "Pattern.h"

class StripedPattern :
    public Pattern
{
public:
    // Constructors
    StripedPattern(const Colour& colourA, const Colour& colourB);
    ~StripedPattern();

    // Utility
    virtual const Colour patternAt(const Point& point) const override;
};

