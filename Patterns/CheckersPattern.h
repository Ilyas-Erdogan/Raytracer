#pragma once
#include "Pattern.h"
class CheckersPattern :
    public Pattern
{
public:
    CheckersPattern(const Colour& colourA, const Colour& colourB);
    ~CheckersPattern();

    virtual const Colour patternAt(const Point& point) const;
};

