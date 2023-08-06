#include "StripedPattern.h"

#include <cmath>

StripedPattern::StripedPattern(const Colour& colourA, const Colour& colourB)
	: Pattern(colourA, colourB)
{
}

StripedPattern::~StripedPattern()
{
	Pattern::~Pattern();
}


/**
* Determines the color of the stripe at the given point.
* 
* @param Point point Reference to the point to check on the pattern.
* 
* @return 
*/
const Colour StripedPattern::patternAt(const Point& point) const
{
	// Check the if the x coordinate is between 0 & 1.
	if (static_cast<int>(std::floor(point.getX())) % 2 == 0)
	{
		return this->a;
	}
	else
	{
		return this->b;
	}
}