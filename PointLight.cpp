#include "PointLight.h"

PointLight::PointLight(const Point& positionVal, const Colour& intensityVal)
	: position{ positionVal }, intensity {intensityVal}
{
}

PointLight::PointLight(const PointLight& pointLightObject)
	: PointLight(pointLightObject.getPosition(), pointLightObject.getIntensity())
{
}

PointLight::~PointLight()
{
}

const Colour& PointLight::getIntensity() const
{
	return this->intensity;
}

const Point& PointLight::getPosition() const
{
	return this->position;
}
