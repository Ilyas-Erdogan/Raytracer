#include "Object.h"
#include "../Intersection.h"
#include <algorithm>

Object::Object()
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ std::make_shared<Material>() }
{
}

Object::Object(const std::shared_ptr<Material>& materialVal)
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ materialVal }
{
}

Object::Object(const Matrix& transformMatrix)
	: transform {transformMatrix}
{
}

Object::Object(const Object& copyObject)
	: Object(Matrix(4, 4).getIdentityMatrix())
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
	return std::shared_ptr<Material>(this->material);
}

/**
* Sets the calling sphere's transformation matrix.
*
* @param Matrix transformMatrix Reference to the matrix to be associated with the Sphere.
*/
void Object::setTransform(const Matrix& transformMatrix)
{
	this->transform = transformMatrix;
}

void Object::setMaterial(std::shared_ptr<Material> newMaterial)
{
	this->material = std::move(newMaterial);
}

/**
* Finds the normal at the given point.
*
* @param Point worldPoint Refernce to the point in the world space to normalize.
*
* @return A vector of the normal at the given point.
*/
Vector Object::normalAt(const Point& worldPoint) const
{
	Matrix inverseTransform = this->getTransform().getInverse();
	Point objectPoint = inverseTransform * worldPoint;

	Vector objectNormal = objectPoint - Point(0, 0, 0);

	Matrix inverseTransposition = this->getTransform().getInverse().getTransposedMatrix();
	Vector worldNormal = inverseTransposition * objectNormal;

	worldNormal = worldNormal.normalizeVector();
	return worldNormal;
}

/**
* Returns a hit from a vector of intersections.
*
* @param vector<Intersection> intersectionVec
*/
std::unique_ptr<Intersection> Object::hit(std::vector<Intersection>& intersectionVec) const
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
			std::unique_ptr<Intersection> returnIntersection(new Intersection(intersection));
			return returnIntersection;
		}
	}

	return nullptr;
}