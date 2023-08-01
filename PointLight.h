#pragma once
#include "Types/Colour.h"
#include "Types/Point.h"

class PointLight
{
public:
	PointLight(const Point& positionVal, const Colour& intensityVal);
	PointLight(const PointLight& pointLightObject);
	~PointLight();

	const Colour& getIntensity() const;
	const Point& getPosition() const;
private:
	Colour intensity;
	Point position;
};

