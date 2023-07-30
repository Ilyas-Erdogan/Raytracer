#pragma once
#include "Types/Colour.h"
#include "PointLight.h"
#include "Types/Vector.h"

class Material
{
public:
	// Constructors
	Material(const Colour& colourVal = Colour(1, 1, 1), const double ambientVal = 0.1, const double diffuseVal = 0.9, const double specularVal = 0.9, const double shininessVal = 200.0);
	~Material();

	// Overloaded operators
	bool operator==(const Material& rhs) const;

	// Getters
	const Colour& getColour() const;
	double getAmbient() const;
	double getDiffuse() const;
	double getSpecular() const;
	double getShininess() const;

	// Setters
	void setColour(const Colour& colourVal);
	void setAmbient(const double ambientVal);
	void setDiffuse(const double diffuseVal);
	void setSpecular(const double specularVal);
	void setShininess(const double shininessVal);

	// Utilities
	Colour lighting(const PointLight& light, const Point& point, const Vector& eyeV, const Vector& normalV) const;
private:
	Colour colour;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
};
