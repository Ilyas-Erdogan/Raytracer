#pragma once
#include "Pattern.h"
#include "../Types/Colour.h"

class RingPattern :
    public Pattern
{
public:
    RingPattern(const Colour& colourA, const Colour& colourB);
    ~RingPattern();

    virtual const Colour patternAt(const Point& point) const;
};

