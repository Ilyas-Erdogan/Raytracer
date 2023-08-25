#include "Intersection.h" 
#include "../Primitives/Sphere.h"

Intersection::Intersection(const double tValue, std::shared_ptr<class Object> initObject)
	: t{ tValue }, object{ std::move(initObject)}
{
}

Intersection::Intersection(const Intersection& copyIntersection)
	: t{ copyIntersection.t }, object{ copyIntersection.object }
{
}

Intersection::~Intersection()
{
}

Intersection& Intersection::operator=(const Intersection& other)
{
	// Self-assignment guard
	if (this == &other)
	{
		return *this;
	}

	this->t = other.t;
	this->object = other.object;

	return *this;
}

/**
* Checks the equality between two intersection objects.
*
* @param Intersection rhs Reference to the right-hand side of the comparison.
*
* @return True if both t values are equal and if both object's point to the same object in memory, otherwise false.
*/
bool Intersection::operator==(const Intersection& rhs) const
{
	bool tCompare = (this->t == rhs.t);
	bool objectCompare = (this->object == rhs.object);

	if (tCompare && objectCompare)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* Checks the equality between two intersection objects.
*
* @param Intersection rhs Reference to the right-hand side of the comparison.
*
* @return True if either t values are not equal and/or if both object's point to the same object in memory, otherwise false.
*/
bool Intersection::operator!=(const Intersection& rhs) const
{
	return !(*this == rhs);
}

/**
* Compares two intersections via their t values.
*
* @param Intersection rhs Reference to the right-hand side of the comparison.
*
* @return True if the calling Intersection's t value is less than that of the right-hand side t value, otherwise false.
*/
bool Intersection::operator<(const Intersection& rhs) const
{
	return (this->t < rhs.t);
}

/**
* @return The calling object's t value.
*/
double Intersection::getT() const
{
	return this->t;
}

/**
* @return A immutable reference to the calling object's object.
*/
const std::shared_ptr<Object> Intersection::getObject() const
{
	return this->object;
}

/**
* Encapsulates data containing precomputed information related to the intersection.
*
* @param Ray ray The ray to be cast in the scene.
* @params std::vector Collection of all the intersections.
*
* @return A Computation object containing all the necessary attributes.
*/
const Computation Intersection::prepareComputations(const Ray& ray, std::vector<Intersection>& xs) const
{
	std::vector<std::shared_ptr<Object>> containers;
	double n1 = 1.0, n2 = 1.0;

	// Precompute necessary values.
	Point tempPoint = ray.getPosition(this->t);
	Vector eyeV = -ray.getDirection();
	Vector normalV = this->getObject()->normalAt(tempPoint);
	bool inside = false; // Default value of inside false.

	// Check for hit occuring inside the object.
	// A negative dot product implies opposite directions.
	if (normalV.dotProduct(eyeV) < 0.0)
	{
		inside = true;
		normalV = -normalV; // Invert normal vector
	}

	Point overPoint = tempPoint + (normalV * 0.00001);
	Point underPoint = tempPoint - (normalV * 0.00001);
	Vector reflectV = ray.getDirection().reflect(normalV);

	for (const Intersection& i : xs)
	{
		// Check if the hit is the intersection.
		if (i == *this)
		{
			// Set the exiting refractive index to 1.
			if (containers.empty())
			{
				n1 = 1.0;
			}
			// Set the exiting refractive index to the last item in the contatiner.
			else
			{
				n1 = containers.back()->getMaterial()->getRefractiveIndex();
			}
		}

		// Check if the intersections object exists in the container.
		std::vector<std::shared_ptr<Object>>::iterator it = std::find(containers.begin(), containers.end(), i.getObject());

		if (it != containers.end())
		{
			// Erase the found item in the container.
			containers.erase(it);
		}
		else
		{
			// Append the item to the container 
			containers.push_back(i.getObject());
		}

		// Check if the hit is the intersection.
		if (i == *this)
		{
			// Set the entering refractive index to 1.
			if (containers.empty())
			{
				n2 = 1.0;
			}
			// Set the entering refractive index to the last item in the contatiner.
			else
			{
				n2 = containers.back()->getMaterial()->getRefractiveIndex();
			}
			// Terminate the loop
			break;
		}
	}

	return Computation(this->t, this->object, tempPoint, eyeV, normalV, inside, overPoint, underPoint, reflectV, n1, n2);
}
