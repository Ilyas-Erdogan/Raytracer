#include "CheckersPattern.h"

#include <cmath>

CheckersPattern::CheckersPattern(const Colour& colourA, const Colour& colourB)
	: Pattern(colourA, colourB)
{
}

CheckersPattern::~CheckersPattern()
{
}

/**
* Determine the colour to display for a the checkers pattern at the given point.
*
* @param Point point Reference to the point to check on the pattern.
*
* @return The current Colour on the pattern.
*/
const Colour CheckersPattern::patternAt(const Point& point) const
{
	if (static_cast<int>((std::floor(point.getX()) + std::floor(point.getY()) + std::floor(point.getZ()))) % 2 == 0)
	{
		return this->a;
	}
	else
	{
		return this->b;
	}
}
