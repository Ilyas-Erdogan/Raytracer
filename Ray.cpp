#include "Ray.h"
#include "Types/Point.h"
#include "Types/Vector.h"
#include "Types/Matrix.h"

/**
* Cosntructs a ray object containing an origin and direction.
* 
* @param Point originPt Origin point of the ray.
* @param Vector directionVec Direction vector of the ray.
*/
Ray::Ray(const Point originPt, const Vector directionVec)
	: origin {originPt}, direction{directionVec}
{
}

/**
* Creates a copy of another ray.
* 
* @param Ray ray Reference to another ray object.
*/
Ray::Ray(const Ray& ray)
	: Ray(ray.origin, ray.direction)
{
}

Ray::~Ray()
{
}

/**
* Returns the calling object's origin point.
* 
* @return Point Origin of the ray.
*/
Point Ray::getOrigin() const
{
	return this->origin;
}

/**
* Returns the calling object's direction vector.
*
* @return Vector Direction of the ray.
*/
const Vector& Ray::getDirection() const
{
	return this->direction;
}

/**
* Returns a Point containing the point at a given distance t.
* 
* @param double t Distance (Time).
* 
* @return Point Position of ray along t.
*/
Point Ray::getPosition(const double t) const
{
	return (this->origin + (t * this->direction));
}

/**
* Transforms the calling ray object using a matrix.
* 
* @param Matrix transformation Reference to the transformation matrix to be applied to the calling ray.
* 
* @return A new Ray with the applied transformation.
*/
Ray Ray::transform(const Matrix& transformation) const
{
	return Ray(transformation * this->getOrigin(), transformation * this->getDirection());
}
