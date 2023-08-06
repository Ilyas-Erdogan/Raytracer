#include "RingPattern.h"

#include <cmath>

RingPattern::RingPattern(const Colour& colourA, const Colour& colourB)
	: Pattern(colourA, colourB)
{
}

RingPattern::~RingPattern()
{
	Pattern::~Pattern();
}

/**
* Determine the colour to display for a the ring pattern at the given point.
* 
* @param Point point Reference to the point to check on the pattern.
*
* @return The current Colour on the pattern.
*/
const Colour RingPattern::patternAt(const Point& point) const
{
	if (static_cast<int>(std::floor(std::sqrt(point.getX() * point.getX() + point.getZ() * point.getZ()))) % 2 == 0)
	{
		return this->a;
	}
	else
	{
		return this->b;
	}
}
