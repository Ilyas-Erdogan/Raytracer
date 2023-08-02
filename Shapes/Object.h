#pragma once
#include <vector>
#include <memory>
#include "../Types/Matrix.h"
#include "../Material.h"
#include <map>

class Object
	: public std::enable_shared_from_this<Object>
{
public:
	// Constructors
	Object();
	Object(const std::shared_ptr<Material>& materialVal);
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

	// Setters
	void setTransform(const Matrix& transformMatrix);
	void setMaterial(std::shared_ptr<Material> newMaterial);

	// Utilities
	Vector normalAt(const Point& p);
	std::unique_ptr<class Intersection> hit(std::vector<class Intersection>& intersctionVec) const;
private:
	Matrix transform;
	std::shared_ptr<Material> material;
	Matrix cachedInverse;
	Matrix cachedInverseTranspose;
};

