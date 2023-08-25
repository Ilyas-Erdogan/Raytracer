#pragma once
#include "Types/Colour.h"
#include "PointLight.h"
#include "Types/Vector.h"
#include "Patterns/Pattern.h"
#include <memory>

class Material
{
public:
	// Constructors
	Material(
		const Colour& colourVal = Colour(1, 1, 1),
		const double ambientVal = 0.1,
		const double diffuseVal = 0.9,
		const double specularVal = 0.9,
		const double shininessVal = 200.0,
		const double reflectiveVal = 0.0,
		const double transparencyVal = 0.0,
		const double refractiveIndexVal = 1.0);
	~Material();

	// Overloaded operators
	bool operator==(const Material& rhs) const;

	// Getters
	const Colour& getColour() const;
	double getAmbient() const;
	double getDiffuse() const;
	double getSpecular() const;
	double getShininess() const;
	const std::shared_ptr<Pattern> getPattern() const;
	double getReflectivity() const;
	double getTransparency() const;
	double getRefractiveIndex() const;

	// Setters
	void setColour(const Colour& colourVal);
	void setAmbient(const double ambientVal);
	void setDiffuse(const double diffuseVal);
	void setSpecular(const double specularVal);
	void setShininess(const double shininessVal);
	void setPattern(std::shared_ptr<Pattern> patternVal);
	void setReflectivity(const double reflectiveVal);
	void setTransparency(const double transparencyVal);
	void setRefractiveIndex(const double refractiveIndexVal);

	// Utilities
	Colour lighting(const std::shared_ptr<class Object>& object, const PointLight& light, const Point& point, const Vector& eyeV, const Vector& normalV, const bool inShadow) const;
	void makeGlassy();
private:
	Colour colour;
	double ambient;
	double diffuse;
	double specular;
	double shininess;

	std::shared_ptr<Pattern> pattern;

	double reflective;
	double transparency;
	double refractiveIndex;
};

