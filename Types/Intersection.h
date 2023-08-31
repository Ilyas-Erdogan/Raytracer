#pragma once
#include "Computation.h"
#include<memory>
#include "../Ray.h"
#include <vector>

class Intersection
{
public:
	// Constructors
	Intersection(const double tValue, std::shared_ptr<class Object> initObject);
	Intersection(const double tValue, std::shared_ptr<class Object> initObject, const double uVal, const double vVal);
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
	double getU() const;
	double getV() const;

	// Utilities
	const Computation prepareComputations(const Ray& ray, const std::vector<Intersection>& xs);

private:
	double t;
	std::shared_ptr<class Object> object;
	double u;
	double v;
};
