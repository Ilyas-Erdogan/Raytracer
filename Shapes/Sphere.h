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
	Sphere(const std::shared_ptr<Material>& materialVal);
	Sphere(const Matrix& transformMatrix);
	Sphere(const Sphere& copySphere);
	Sphere(const Object& copyObject);
	~Sphere();

	// Utilities
	std::vector<class Intersection> intersect(const class Ray& ray);
	std::unique_ptr<Intersection> hit(std::vector<Intersection>& intersctionVec) const;
	Vector normalAt(const Point& p) const;

	// Getters
	const Matrix& getTransform() const;
	const Material& getMaterial() const;

	// Setters
	void setTransform(const Matrix& transformMatrix);
	void setMaterial(std::shared_ptr<Material> newMaterial);
private:
	Matrix transform;
	std::shared_ptr<Material> material;

};

