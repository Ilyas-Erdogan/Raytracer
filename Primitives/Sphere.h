#pragma once
#include "Object.h"
#include "../Types/Matrix.h"
#include "../Types/Vector.h"
#include "../Types/Point.h"
#include "../Material.h"


class Sphere
	: public Object, public std::enable_shared_from_this<Sphere>
{
public:
	// Constructors
	Sphere();
	Sphere(const Matrix& transformMatrix);
	Sphere(const Sphere& copySphere);
	Sphere(const Object& copyObject);
	~Sphere();


	// Utilities
	virtual const std::vector<Intersection> localIntersect(const class Ray& localRay);
	virtual const Vector localNormalAt(const class Point& localPoint) const;
};

