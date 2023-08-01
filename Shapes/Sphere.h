#pragma once
#include "Object.h"
#include "../Types/Matrix.h"
#include "../Types/Vector.h"
#include "../Types/Point.h"
#include "../Material.h"

class Sphere
	: public Object
{
public:
	// Constructors
	Sphere();
	Sphere(const Matrix& transformMatrix);
	Sphere(const Sphere& copySphere);
	Sphere(const Object& copyObject);
	~Sphere();


	// Utilities
	std::vector<class Intersection> intersect(const class Ray& ray);
};

