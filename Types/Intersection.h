#pragma once
#include<memory>
#include "Computation.h"
#include "../Ray.h"

class Intersection
{
public:
	// Constructors
	Intersection(const double tValue, const std::shared_ptr<class Object>& initObject);
	Intersection(const Intersection& copyIntersection);
	~Intersection();

	// Overloaded operators
	Intersection& operator=(const Intersection& other);
	bool operator==(const Intersection& rhs) const;
	bool operator!=(const Intersection& rhs) const;
	bool operator<(const Intersection& rhs) const;

	// Getters
	double getT() const;
	const std::shared_ptr<class Object> getObject() const;

	// Utilities
	const Computation prepareComputations(const Ray& ray) const;
private:
	double t;
	std::shared_ptr<class Object> object;
};
