#pragma once
#include "Object.h"

class Triangle
	: public Object, public std::enable_shared_from_this<Triangle>
{
public:
	Triangle(const Point& pointOne, const Point& pointTwo, const Point& pointThree);
	~Triangle();

	std::shared_ptr<Triangle> toTriangle() override;

	virtual const std::vector<class Intersection> localIntersect(const class Ray& localRay);
	virtual const Vector localNormalAt(const class Point& localPoint, const Intersection& hit) const;

	const Point& getPointOne() const;
	const Point& getPointTwo() const;
	const Point& getPointThree() const;
	const Vector& getEdgeOne() const;
	const Vector& getEdgeTwo() const;
	const Vector& getNormal() const;
protected:
	const double EPSILON{ 0.00001 };
	Point p1;
	Point p2;
	Point p3;
	Vector e1;
	Vector e2;
	Vector normal;
};
