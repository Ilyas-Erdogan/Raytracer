#pragma once
#include "../Types/Point.h"
#include "../Types/Vector.h"
#include "../Primitives/Object.h"

class Computation
{
public:
	// Constructors
	Computation(
		const double tVal,
		std::shared_ptr<class Object> initObject,
		const Point& pointVal,
		const Vector& eyeVVal,
		const Vector& normalVVal,
		const bool insideVal,
		const Point& overPointVal,
		const Point& underPointVal,
		const Vector& reflectVVal,
		const double n1Val = 1.0,
		const double n2Val = 1.0);
	Computation(const Computation& copyComputation);
	~Computation();

	// Getters
	double getT() const;
	const std::shared_ptr<class Object>& getObject() const;
	const Point& getPoint() const;
	const Vector& getEyeV() const;
	const Vector& getNormalV() const;
	const Point& getOverPoint() const;
	bool isInside() const;
	const Vector& getReflectV() const;
	double getEnter() const;
	double getExit() const;
	const Point& getUnderPoint() const;

	// Utility
	double schlick() const;
private:
	double t;
	std::shared_ptr<class Object> object;
	Point point;
	Vector eyeV;
	Vector normalV;
	bool inside;
	Point overPoint;
	Vector reflectV;
	double n1;
	double n2;
	Point underPoint;
};
