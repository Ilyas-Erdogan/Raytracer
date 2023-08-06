#include "GradientPattern.h"

#include <cmath>

GradientPattern::GradientPattern(const Colour& colourA, const Colour& colourB)
	: Pattern(colourA, colourB)
{
}

GradientPattern::~GradientPattern()
{
	Pattern::~Pattern();
}

/**
* Implementatin of a blending function. Takes two values and interpolates the values between them.
* 
* @param Point point Reference to the point to check on the pattern.
* 
* @return The current Colour on the pattern.
*/
const Colour GradientPattern::patternAt(const Point& point) const
{
	// Find the distance between two colours
	Colour distance = this->b - this->a;
	// Find fractional position of the x coordinate.
	double fraction = point.getX() - std::floor(point.getX());

	return (this->a + distance * fraction);
}
