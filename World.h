#pragma once
#include <vector>
#include <memory>
#include "PointLight.h"
#include "Intersection.h"
#include "Ray.h"

class World
{
public:
	// Constructors
	World(const bool setDefault);
	~World();

	// Getters
	const PointLight& getLightSource() const;
	const std::vector<std::shared_ptr<class Sphere>>& getObjects() const;

	// Setters
	void setLight(const PointLight& pointLight);
	void addObjects(const std::shared_ptr<Sphere> objectToAdd);

	// Utilities
	const std::vector<Intersection> intersectWorld(const Ray& ray);
	const Colour shadeHit(const Computation& computation) const;
	const Colour colourAt(const Ray& ray);
private:
	std::vector<std::shared_ptr<class Sphere>> objects;
	std::unique_ptr<class PointLight> light;
};

