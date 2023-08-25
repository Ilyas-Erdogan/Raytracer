#pragma once
#include <vector>
#include <memory>
#include "../Types/Matrix.h"
#include "../Ray.h"
#include <memory>

class Object
{
public:
	// Constructors
	Object();
	Object(std::shared_ptr<class Material> materialVal);
	Object(const Matrix& transformMatrix);
	Object(const Object& copyObject);
	~Object();

	// Overloaded Operators
	Object& operator=(const Object& other);
	bool operator==(const Object& rhs) const;
	bool operator!=(const Object& rhs) const;

	// Getters
	std::vector<class Intersection> getIntersections(const std::vector<Intersection>& intersections) const;
	const Matrix& getTransform() const;
	const std::shared_ptr<class Material> getMaterial() const;
	const Matrix& getCachedInverse() const;
	const Matrix& getCachedInverseTranspose() const;
	const Ray& getSavedRay() const;

	// Setters
	void setTransform(const Matrix& transformMatrix);
	void setMaterial(std::shared_ptr<Material> newMaterial);

	// Utilities
	std::shared_ptr<class Intersection> hit(std::vector<class Intersection>& intersctionVec) const;

	virtual const std::vector<class Intersection> localIntersect(const class Ray& localRay) = 0;
	const std::vector<class Intersection> intersect(const Ray& ray);

	virtual const Vector localNormalAt(const class Point& localPoint) const = 0;
	const Vector normalAt(const class Point& point);
private:
	Matrix transform;
	std::shared_ptr<Material> material;
	Matrix cachedInverse;
	Matrix cachedInverseTranspose;

	Ray savedRay = Ray(Point(0,0,0), Vector(0,0,0));
};

