#pragma once
#include "Types/Point.h"
#include "Types/Vector.h"


class Ray
{
public:
	Ray(const Point originPt, const Vector directionVec);
	Ray(const Ray& ray);
	~Ray();

	Point getOrigin() const;
	const Vector& getDirection() const;
	Point getPosition(const double t) const;
	Ray transform(const class Matrix& transformation) const;
private:
	Point origin; // Starting point
	Vector direction; // Where it points
};

