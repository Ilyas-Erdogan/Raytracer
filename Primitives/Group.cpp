#include "Group.h"
#include "../Types/Intersection.h"
#include <algorithm>

Group::Group(const std::string name)
	: Object(), name{name}
{
}

Group::~Group()
{
	Object::~Object();
}

/**
* Returns a collection of all the Intersections from the children of a group.
*
* @param Ray localRay Reference to the local ray to be checked whether or not it intersects with the sphere.
*
* @return A sorted vector of all solutions of the equations.
*/
const std::vector<class Intersection> Group::localIntersect(const Ray& localRay)
{
	std::vector<Intersection> intersections;
	for (const std::shared_ptr<Object>& child : this->children)
	{
		std::vector<Intersection> childIntersects = child->intersect(localRay);
		intersections.insert(intersections.end(), childIntersects.begin(), childIntersects.end());
	}

	std::sort(intersections.begin(), intersections.end());
	
	return intersections;
}

const Vector Group::localNormalAt(const class Point& localPoint, const Intersection& hit) const
{
	throw std::exception("Groups do not need this function.");
}

std::shared_ptr<class Group> Group::toGroup()
{
	return shared_from_this();
}

/**
* @return True if the list of children is empty, otherwise false.
*/
const bool Group::isEmpty() const
{
	return this->children.empty();
}

/**
* @return An immutable reference to the children of the calling group.
*/
const std::vector<std::shared_ptr<Object>>& Group::getChildren() const
{
	return this->children;
}

/**
* Sets the calling group as the parent of the shape parameter, and adds the shape as a child of the calling group.
* 
* @param shared_ptr<Object> shape An immutable reference to the shape. 
*/
void Group::addChild(const std::shared_ptr<Object>& shape)
{
	shape->setParent(shared_from_this());
	shape->setMaterial(this->getMaterial());
	this->children.push_back(shape);
}

const std::string Group::getName() const
{
	return this->name;
}
