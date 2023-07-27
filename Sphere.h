#pragma once
#include "Object.h"
#include "Types/Matrix.h"

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
	std::unique_ptr<Intersection> hit(std::vector<Intersection>& intersctionVec) const;

	// Getters
	const Matrix& getTransform() const;

	// Setters
	void setTransform(const Matrix& transformMatrix);
private:
	Matrix transform;
};

