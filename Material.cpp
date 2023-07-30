#include "Material.h"
#include <cmath>

Material::Material(const Colour& colourVal, const double ambientVal, const double diffuseVal, const double specularVal, const double shininessVal)
	: colour {colourVal}, ambient {ambientVal}, diffuse {diffuseVal}, specular {specularVal}, shininess {shininessVal}
{
}

Material::~Material()
{
}

/**
* Checks for equality between attributes of two materials.
* 
* @param Material rhs Right-hand side reference to the material to be compared with the calling object.
* 
* @return True is all attributes are identitical, otherwise false.
*/
bool Material::operator==(const Material& rhs) const
{
	bool colourCheck = (this->colour == rhs.colour);
	bool ambientCheck = (this->ambient == rhs.ambient);
	bool diffuseCheck = (this->diffuse == rhs.diffuse);
	bool specularCheck = (this->specular == rhs.specular);
	bool shininessCheck = (this->shininess == rhs.shininess);
	return (colourCheck && ambientCheck && diffuseCheck && specularCheck && shininessCheck);
}

/**
* @return An immutable reference to the Colour attribute of the material.
*/
const Colour& Material::getColour() const
{
	return this->colour;
}

/**
* @return The ambient attribute of the material.
*/
double Material::getAmbient() const
{
	return this->ambient;
}

/**
* @return The diffuse diffuse of the material.
*/
double Material::getDiffuse() const
{
	return this->diffuse;
}

/**
* @return The specular attribute of the material.
*/
double Material::getSpecular() const
{
	return this->specular;
}

/**
* @return The shininess attribute of the material.
*/
double Material::getShininess() const
{
	return this->shininess;
}

/**
* Sets the colour of the material.
* 
* @param Colour colourVal Reference to the colour to be assigned to the material.
*/
void Material::setColour(const Colour& colourVal)
{
	this->colour = colourVal;
}

/**
* Sets the ambience of the material.
*
* @param double ambientVal Ambience to be assigned to the material.
*/
void Material::setAmbient(const double ambientVal)
{
	this->ambient = ambientVal;
}

/**
* Sets the diffuse of the material.
*
* @param double diffuseVal Diffuse to be assigned to the material.
*/
void Material::setDiffuse(const double diffuseVal)
{
	this->diffuse = diffuseVal;
}

/**
* Sets the specular of the material.
*
* @param double specularVal Specular to be assigned to the material.
*/
void Material::setSpecular(const double specularVal)
{
	this->diffuse = specularVal;
}

/**
* Sets the shininess of the material.
*
* @param double shininess Shininess to be assigned to the material.
*/
void Material::setShininess(const double shininessVal)
{
	this->shininess = shininessVal;
}

/**
* Applies the Phong reflection model by combining the calling material's ambient, diffuse, and specular components.
* 
* @param PointLight light Reference to the point being illuminated.
* @param Point point Reference the light source.
* @param Vector eyeV Reference to the eye.
* @param Vector normalV Reference to the normal vectors from the reflection model.
* 
* @return The colour to be applied to a pixel given the parameters.
*/
Colour Material::lighting(const PointLight& light, const Point& point, const Vector& eyeV, const Vector& normalV) const
{
	// Combine surface colour with light's colour/intensity
	Colour effectiveColour = this->colour * light.getIntensity();
	// Find direction to light source
	Vector lightV = (light.getPosition() - point).normalizeVector();
	// Compute the ambient contribution
	Colour ambient = static_cast<Tuple>(effectiveColour) * this->ambient;

	Colour diffuse;
	Colour specular;
	// lightDotNormal represents the cosine of the angle between the light and normal vector.
	double lightDotNormal = lightV.dotProduct(normalV);

	if (lightDotNormal >= 0.0)
	{
		// Compute the diffuse contribution
		diffuse = static_cast<Tuple>(effectiveColour) * this->diffuse * lightDotNormal;

		// reflectDotEye represents the cosine of the angle between the reflectino and eye vector.
		Vector reflectV = -lightV.reflect(normalV);
		double reflectDotEye = reflectV.dotProduct(eyeV);

		if (reflectDotEye > 0.0)
		{
			double factor = std::pow(reflectDotEye, this->shininess);
			specular = static_cast<Tuple>(light.getIntensity()) * this->specular * factor;
		}
	}

	return (ambient + diffuse + specular);
}
