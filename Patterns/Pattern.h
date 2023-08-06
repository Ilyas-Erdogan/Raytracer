#pragma once
#include "../Types/Colour.h"
#include "../Types/Point.h"
#include "../Types/Matrix.h"
#include "../Primitives/Object.h"
#include <memory>

class Pattern
{
public:
	// Constructors
	Pattern(const Colour& colourA, const Colour& colourB);
	~Pattern();

	// Getters
	const Colour& getA() const;
	const Colour& getB() const;
	const Matrix& getTransform() const;

	// Setters
	void setPatternTransform(const Matrix& transformation);

	// Utilites
	virtual const Colour patternAt(const Point& point) const;
	virtual const Colour patternAtShape(const std::shared_ptr<class Object>& shape, const Point& point);
protected:
	Colour a;
	Colour b;
	Matrix transform;
	Matrix cachedInverse;
};

