#include "Material.h"
#include "Primitives/Object.h"
#include <cmath>

/**
* Constructs a Material with the given attributes.
* 
* @param Colour colourVal Reference to the Colour to be attribute of the material.
* @param double ambientVal Value of the ambient attribute of the material. Typical Range : [0.0, 1.0]. 
* @param double diffuseVal Value of the diffuse attribute of the material. Typical Range : [0.0, 1.0].
* @param double specularVal Value of the specular attribute of the material. Typical Range : [0.0, 1.0].
* @param double shininessVal Value of the shininess attribute of the material. Typical Range : [10.0, 200.0].
*/
Material::Material(
	const Colour& colourVal,
	const double ambientVal,
	const double diffuseVal, 
	const double specularVal, 
	const double shininessVal, 
	const double reflectiveVal,
	const double transparencyVal,
	const double refractiveIndexVal)
	: colour {colourVal}, ambient {ambientVal}, diffuse {diffuseVal}, specular {specularVal}, shininess {shininessVal}, reflective{reflectiveVal}, transparency{transparencyVal}, refractiveIndex{refractiveIndexVal}
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
* @return A shared pointer to the pattern of the material.
*/
const std::shared_ptr<Pattern> Material::getPattern() const
{
	return this->pattern;
}

/**
* @return The reflectivity of the material.
*/
double Material::getReflectivity() const
{
	return this->reflective;
}

/**
* @return The transparency of the material.
*/
double Material::getTransparency() const
{
	return this->transparency;
}

/**
* @return The refractive index of the material.
*/
double Material::getRefractiveIndex() const
{
	return this->refractiveIndex;
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
	this->specular = specularVal;
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
* Sets the pattern of the material.
*
* @param shared_ptr<Pattern> patternVal Pattern to be assigned to the material.
*/
void Material::setPattern(std::shared_ptr<Pattern> patternVal)
{
	this->pattern = std::move(patternVal);
}

/**
* Sets the reflectivity of the material.
*
* @param double reflectiveVal Reflectivity value to be assigned to the material.
*/
void Material::setReflectivity(const double reflectiveVal)
{
	this->reflective = reflectiveVal;
}

/**
* Sets the transparency of the material.
*
* @param double transparencyVal Transparency value to be assigned to the material.
*/
void Material::setTransparency(const double transparencyVal)
{
	this->transparency = transparencyVal;
}

/**
* Sets the refractive index of the material.
*
* @param double refractiveIndexVal Refractive index to be assigned to the material.
*/
void Material::setRefractiveIndex(const double refractiveIndexVal)
{
	this->refractiveIndex = refractiveIndexVal;
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
Colour Material::lighting(const std::shared_ptr<Object>& object, const PointLight& light, const Point& point, const Vector& eyeV, const Vector& normalV, const bool inShadow) const
{
	Colour colour; // note not the same at this->colour!!!
	if (this->pattern != nullptr)
	{
		colour = this->pattern->patternAtShape(object, point);
	}
	else
	{
		colour = this->colour;
	}
	// Combine surface colour with light's colour/intensity
	Colour effectiveColour = colour * light.getIntensity();
	// Find direction to light source
	Vector lightV = (light.getPosition() - point).normalizeVector();
	// Compute the ambient contribution
	Colour ambient = static_cast<Tuple>(effectiveColour) * this->ambient;

	Colour diffuse;
	Colour specular;
	// Ignore diffuse and specular values if in shadow
	if (!inShadow)
	{
		// lightDotNormal represents the cosine of the angle between the light and normal vector.
		double lightDotNormal = lightV.dotProduct(normalV);
		if (lightDotNormal < 0)
		{
			lightDotNormal *= -1;
		}
		if (lightDotNormal >= 0.0)
		{
			// Compute the diffuse contribution
			diffuse = static_cast<Tuple>(effectiveColour) * this->diffuse * lightDotNormal;

			// reflectDotEye represents the cosine of the angle between the reflection and eye vector.
			Vector reflectV = -lightV.reflect(normalV);
			double reflectDotEye = reflectV.dotProduct(eyeV);

			if (reflectDotEye > 0.0)
			{
				double factor = std::pow(reflectDotEye, this->shininess);
				specular = static_cast<Tuple>(light.getIntensity()) * this->specular * factor;
			}
		}
	}

	return (ambient + diffuse + specular);
}

/**
* Creates glassy material by setting specific transparency and refractive indexs values.
*/
void Material::makeGlassy()
{
	this->transparency = 1.0;
	this->refractiveIndex = 1.5;
}