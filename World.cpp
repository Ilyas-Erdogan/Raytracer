#include "World.h"
#include "PointLight.h"
#include "Shapes/Sphere.h"
#include "Transformations/Scale.h"
#include <algorithm>

World::World(const bool setDefault)
{
	if (setDefault)
	{
		std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>();
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->setColour(Colour(0.8, 1.0, 0.6));
		material->setDiffuse(0.7);
		material->setSpecular(0.2);
		s1->setMaterial(material);

		std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>();
		s2->setTransform(Scale(0.5, 0.5, 0.5));

		this->objects.push_back(s1);
		this->objects.push_back(s2);
		this->light = std::make_unique<PointLight>(Point(-10, 10, -10), Colour(1, 1, 1));
	}
	else
	{
		this->objects.shrink_to_fit();
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
* Finds all the intersections in the world using a given point.
* 
* @param Ray ray Reference to the ray to be cast in the world.
* 
* @return An immutable vector of the intersections found with the given ray.
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

const Colour World::colourAt(const Ray& ray)
{
	// Find intersections with given ray
	std::vector<Intersection> intersections = this->intersectWorld(ray);

	// Find hit from resulting intersections
	std::unique_ptr<Intersection> hitCheck = Object().hit(intersections);
	if (hitCheck == nullptr)
	{
		return Colour();
	}
	else
	{
		Computation comp = hitCheck->prepareComputations(ray);
		return this->shadeHit(comp);
	}
}
