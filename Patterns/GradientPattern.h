#pragma once
#include "Pattern.h"
class GradientPattern :
    public Pattern
{
public:
    GradientPattern(const Colour& colourA, const Colour& colourB);
    ~GradientPattern();

    virtual const Colour patternAt(const Point& point) const;
};

