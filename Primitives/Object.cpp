#include "Object.h"
#include "../Types/Intersection.h"
#include "../Material.h"

#include <algorithm>

#include "Group.h"

Object::Object()
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ std::make_shared<Material>() }, parent{nullptr}
{
	this->cachedInverse = this->transform;
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(std::shared_ptr<Material> materialVal)
	: transform{ Matrix(4, 4).getIdentityMatrix() }, material{ materialVal }, parent{ nullptr }
{
	this->cachedInverse = this->transform;
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(const Matrix& transformMatrix)
	: transform {transformMatrix}, material{std::make_shared<Material>()}, parent{ nullptr }
{
	this->cachedInverse = this->transform.getInverse();
	this->cachedInverseTranspose = this->cachedInverse.getTransposedMatrix();
}

Object::Object(const Object& copyObject)
	: transform{ copyObject.getTransform() }, material{ copyObject.getMaterial() }, cachedInverse{ copyObject.getCachedInverse() }, cachedInverseTranspose{ copyObject.getCachedInverseTranspose() }, parent{copyObject.parent}
{
}

Object::~Object()
{
}

std::shared_ptr<class Triangle> Object::toTriangle()
{
	throw std::exception("NO");
}

std::shared_ptr<class Group> Object::toGroup()
{
	throw std::exception("NO");
}

std::shared_ptr<class SmoothTriangle> Object::toSmoothTriangle()
{
	throw std::exception("NO");
}



Object& Object::operator=(const Object& other)
{
	if (this == &other)
	{
		*this = other;
	}

	this->transform = other.transform;
	this->material = other.material;
	this->cachedInverse = other.cachedInverse;
	this->cachedInverseTranspose = other.cachedInverseTranspose;
	this->savedRay = other.savedRay;
	this->parent = other.parent;
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
	if (this->parent != nullptr)
	{
		return this->parent->getMaterial();
	}
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
	this->material = newMaterial;
}

/**
* Returns a hit from a vector of intersections.
*
* @param vector<Intersection> intersectionVec The vector of found containing the intersections found by the ray.
* 
* @return A unique pointer of the Intersection.
*/
std::shared_ptr<Intersection> Object::hit(const std::vector<Intersection>& intersectionVec) const
{
	// Early check for empty vector
	if (intersectionVec.empty())
	{
		return nullptr;
	}

	// Sort the vector for iteration optimization
	// Iterate through the vector until first positive result is found
	for (const Intersection& intersection : intersectionVec)
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
* Finds the normal on a child object of a group, 
* taking into account transformations on both the child object and the parent(s).
*
* @param Point worldPoint Reference to the point in the world space to normalize.
*
* @return A vector of the normal at the given point.
*/
const Vector Object::normalAt(Point& worldPoint, const Intersection& hit)
{
	// Convert world-space point to object space
	Point localPoint = this->worldToObject(worldPoint);
	// Calculate the normal
	Vector localNormal = this->localNormalAt(localPoint, hit);
	// Convert the nroaml back to world space
	return this->normalToWorld(localNormal);
}

/**
* @return An immutable reference to the parent of the calling object.
*/
const std::shared_ptr<Group>& Object::getParent() const
{
	return this->parent;
}

/**
* Sets a new parent of the calling object.
* 
* @param shared_ptr<Group> newParent The new group to set as the parent of the calling object.
*/
void Object::setParent(std::shared_ptr<class Group> newParent)
{
	this->parent = std::move(newParent);
}

/**
* Converts a point in world space and trasnforms it into object space.
* 
* @param Point worldPoint Reference to point in world space.
* 
* @return The point in object space.
*/
const Point Object::worldToObject(Point& worldPoint) const
{
	// Check if shape has a parent
	if (this->parent != nullptr)
	{
		// Convert the point to its parent's space
		worldPoint = this->parent->worldToObject(worldPoint);
	}

	return this->cachedInverse * worldPoint;
}

/**
* Converts a normal in world space and trasnforms it into object space.
*
* @param Vector worldNormal Reference to normal in world space.
*
* @return The normal in object space.
*/
const Vector Object::normalToWorld(Vector& normalWorld) const
{
	normalWorld = this->cachedInverseTranspose * normalWorld;
	normalWorld = Tuple(normalWorld.getX(), normalWorld.getY(), normalWorld.getZ(), 0);
	normalWorld = normalWorld.normalizeVector();

	// Check for parent
	if (this->parent != nullptr)
	{
		// Recurisve pass
		normalWorld = this->parent->normalToWorld(normalWorld);
	}

	return normalWorld;
}
