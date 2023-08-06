#include "Pattern.h"

#include "../Primitives/Object.h"

Pattern::Pattern(const Colour& colourA, const Colour& colourB)
	: a{ colourA }, b{ colourB }, transform{Matrix(4, 4).getIdentityMatrix()}, cachedInverse{Matrix(4, 4).getIdentityMatrix()}
{
}

Pattern::~Pattern()
{
}

/**
* @return An immutable reference to the primary colour of the pattern.
*/
const Colour& Pattern::getA() const
{
	return this->a;
}

/**
* @return An immutable reference to the secondary colour of the pattern.
*/
const Colour& Pattern::getB() const
{
	return this->b;
}

/**
* @return An immutable reference to the transform applied to the pattern.
*/
const Matrix& Pattern::getTransform() const
{
	return this->transform;
}

/**
* Caches the transformation matrix as well as its inverse.
* 
* @param Matrix transformation Reference to the transformation matrix to be applied to the matrix.
*/
void Pattern::setPatternTransform(const Matrix& transformation)
{
	this->transform = transformation;
	this->cachedInverse = transformation.getInverse();
}

/**
* Finds the colour at the given point.
* 
* @param Point point Reference to the point to Colour check.
* 
* @return The current Colour in the pattern.
*/

const Colour Pattern::patternAt(const Point& point) const
{
	return Colour(point.getX(), point.getY(), point.getZ());
}

/**
* Gets the given colour of a pattern on a specific object.
*
* @param shared_ptr<Object> object An immutable reference to pointer of the object to check.
* @param Point point An immutable reference to the point in the world space.
*
* @return The Colour for the given pattern on the given object.
*/
const Colour Pattern::patternAtShape(const std::shared_ptr<Object>& object, const Point& point)
{
	// Convert the point to object space.
	Point objectPoint = object->getCachedInverse() * point;
	// Convert to pattern space.
	Point patternPoint = this->cachedInverse * objectPoint;

	return this->patternAt(patternPoint);
}

