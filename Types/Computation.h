#pragma once
#include "../Types/Point.h"
#include "../Types/Vector.h"
#include "../Primitives/Object.h"

class Computation
{
public:
	// Constructors
	Computation(const double tVal, std::shared_ptr<class Object> initObject, const Point& pointVal, const Vector& eyeVVal, const Vector& normalVVal, const bool insideVal, const Point& overPointVal, const Vector& reflectVVal);
	~Computation();

	// Getters
	double getT() const;
	const std::shared_ptr<class Object> getObject() const;
	const Point& getPoint() const;
	const Vector& getEyeV() const;
	const Vector& getNormalV() const;
	const Point& getOverPoint() const;
	bool isInside() const;
	const Vector& getReflectV() const;

private:
	double t;
	std::shared_ptr<class Object> object;
	Point point;
	Vector eyeV;
	Vector normalV;
	bool inside;
	Point overPoint;
	Vector reflectV;
};
