#include "World.h"
#include "PointLight.h"
#include "Shapes/Sphere.h"
#include "Transformations/Scale.h"
#include <algorithm>

/**
* Creates an empty or default world according to parameter.
* 
* @param bool setDefault If true, a default world with two spheres & a default point light are constructed, otherwise the world is empty,
*/
World::World(const bool setDefault)
{
	if (setDefault)
	{
		// Create first sphere
		std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>();
		// Create a material
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->setColour(Colour(0.8, 1.0, 0.6));
		material->setDiffuse(0.7);
		material->setSpecular(0.2);
		// Set the first spehre's material
		s1->setMaterial(material);

		// Create second sphere
		std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>();
		s2->setTransform(Scale(0.5, 0.5, 0.5));

		// Add spheres to scene
		this->objects.push_back(s1);
		this->objects.push_back(s2);
		// Set light source
		this->light = std::make_unique<PointLight>(Point(-10, 10, -10), Colour(1, 1, 1));
	}
	else
	{
		// Resize list of objects to 0
		this->objects.shrink_to_fit();
		// Set light to empty non-existent
		this->light = nullptr;
	}
}

World::~World()
{
}

/**
* @return An immutable reference to the light source in the world.
*/
const PointLight& World::getLightSource() const
{
	return *this->light;
}

/**
* @return An immutable vector of the objects in the world.
*/
const std::vector<std::shared_ptr<class Sphere>>& World::getObjects() const
{
	return this->objects;
}

/**
* Sets the light in the current world.
* 
* @param PointLight pointLight Reference to the point light to set in the scene.
*/
void World::setLight(const PointLight & pointLight)
{
	this->light = std::make_unique<PointLight>(pointLight);
}

/**
* Adds objects to the world.
* 
* @param shared_ptr<Sphere> objectToAdd Object to add to the world in the objects list.
*/
void World::addObjects(const std::shared_ptr<Sphere> objectToAdd)
{
	this->objects.emplace_back(objectToAdd);
}

/**
* Finds all the intersections in the world using a given point and aggregates them into a list.
* 
* @param Ray ray Reference to the ray to be cast in the world.
* 
* @return An \a sorted immutable vector of the intersections found with the given ray.
*/
const std::vector<Intersection> World::intersectWorld(const Ray& ray)
{
	std::vector<Intersection> intersections;
	// Iterate over all objects in the world and check for intersections.
	for (auto sphereObject : this->objects)
	{
		std::vector<Intersection> intersectionSub = (*sphereObject).intersect(ray);
		if (intersectionSub.size() != 0)
		{
			intersections.emplace_back(intersectionSub[0]);
			intersections.emplace_back(intersectionSub[1]);
		}
	}
	// Sort over intersection objects
	std::sort(intersections.begin(), intersections.end());

	return intersections;
}

/**
* @param Computation computation A reference to the computation to find the intersected colour with.
* 
* @return The colour at the intersection encapsualted by the proivded compuatation.
*/
const Colour World::shadeHit(const Computation& computation) const
{
	return computation.getObject()->getMaterial()->lighting(this->getLightSource(), computation.getPoint(), computation.getEyeV(), computation.getNormalV());
}

/**
* Determines colour found in the scene determined by the cast ray.
* 
* @param Ray ray Reference to the ray being cast in the scene.
* 
* @return An immutable Colour (to be drawn onto the canvas).
*/
const Colour World::colourAt(const Ray& ray)
{
	// Find intersections with given ray
	std::vector<Intersection> intersections = this->intersectWorld(ray);

	// Find hit from resulting intersections
	std::unique_ptr<Intersection> hitCheck = utilObject.hit(intersections);
	// If no hits are found, return a black colour
	if (hitCheck == nullptr)
	{
		return Colour();
	}
	else
	{
		// Prepare the appropraite computations to be used for shading.
		Computation comp = hitCheck->prepareComputations(ray);
		// Determine Colour to be written.
		return this->shadeHit(comp);
	}
}
