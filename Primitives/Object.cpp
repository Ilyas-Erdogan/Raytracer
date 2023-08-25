#include "Object.h"
#include "../Types/Intersection.h"
#include "../Material.h"

#include <algorithm>

Object::Object()
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ std::make_shared<Material>() }
{
	this->cachedInverse = this->transform;
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(std::shared_ptr<Material> materialVal)
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ materialVal }
{
	this->cachedInverse = this->transform;
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(const Matrix& transformMatrix)
	: transform {transformMatrix}, material{std::make_shared<Material>()}
{
	this->cachedInverse = this->transform.getInverse();
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(const Object& copyObject)
	: transform{copyObject.getTransform()}, material{copyObject.getMaterial()}, cachedInverse{copyObject.getCachedInverse()}, cachedInverseTranspose{copyObject.getCachedInverseTranspose()}
{
}

Object::~Object()
{
}

Object& Object::operator=(const Object& other)
{
	*this = other;
	return *this;
}

bool Object::operator==(const Object& rhs) const
{
	return (this == &rhs);
}

bool Object::operator!=(const Object& rhs) const
{
	return !(*this == rhs);
}

std::vector<Intersection> Object::getIntersections(const std::vector<Intersection>& intersections) const
{
	return std::vector<Intersection>(intersections);
}

/**
* @return An immutable reference to the current transformation of the Sphere.
*/
const Matrix& Object::getTransform() const
{
	return this->transform;
}

/**
* @return An immutable reference to teh current material of the Sphere.
*/
const std::shared_ptr<Material> Object::getMaterial() const
{
	return this->material;
}

const Matrix& Object::getCachedInverse() const
{
	return this->cachedInverse;
}

const Matrix& Object::getCachedInverseTranspose() const
{
	return this->cachedInverseTranspose;
}

const Ray& Object::getSavedRay() const
{
	return this->savedRay;
}

/**
* Sets the calling sphere's transformation matrix.
*
* @param Matrix transformMatrix Reference to the matrix to be associated with the Sphere.
*/
void Object::setTransform(const Matrix& transformMatrix)
{
	this->transform = transformMatrix;
	this->cachedInverse = transformMatrix.getInverse();
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

void Object::setMaterial(std::shared_ptr<Material> newMaterial)
{
	this->material = std::move(newMaterial);
}

/**
* Returns a hit from a vector of intersections.
*
* @param vector<Intersection> intersectionVec The vector of found containing the intersections found by the ray.
* 
* @return A unique pointer of the Intersection.
*/
std::shared_ptr<Intersection> Object::hit(std::vector<Intersection>& intersectionVec) const
{
	// Early check for empty vector
	if (intersectionVec.empty())
	{
		return nullptr;
	}

	// Sort the vector for iteration optimization
	std::sort(intersectionVec.begin(), intersectionVec.end());
	// Iterate through the vector until first positive result is found
	for (Intersection& intersection : intersectionVec)
	{
		if (intersection.getT() > 0.0)
		{
			//std::unique_ptr<Intersection> returnIntersection(new Intersection(intersection));
			return std::make_shared<Intersection>(intersection);
		}
	}

	return nullptr;
}

/**
* Returns a collection of Intersections.
*
* @param Ray ray Reference to the ray to be checked whether or not it intersects with the sphere.
*
* @return A vector of all intersections from the given ray.
*/
const std::vector<Intersection> Object::intersect(const Ray& ray)
{
	Ray localRay = ray.transform(this->getCachedInverse());
	this->savedRay = localRay;

	return this->localIntersect(localRay);
}

/**
* Finds the normal at the given point.
*
* @param Point worldPoint Refernce to the point in the world space to normalize.
*
* @return A vector of the normal at the given point.
*/
const Vector Object::normalAt(const Point& worldPoint)
{
	Point localPoint = this->getCachedInverse() * worldPoint;

	Vector localNormal = this->localNormalAt(localPoint);

	Vector worldNormal = this->getCachedInverseTranspose() * localNormal;

	return worldNormal.normalizeVector();
}