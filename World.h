#pragma once
#include <vector>
#include <memory>
#include "PointLight.h"
#include "Types/Intersection.h"
#include "Ray.h"
#include "Primitives/Object.h"

class World
{
public:
	// Constructors
	World(const bool setDefault);
	~World();

	// Getters
	const PointLight& getLightSource() const;
	const std::vector<std::shared_ptr<class Object>>& getObjects() const;

	// Setters
	void setLight(const PointLight& pointLight);
	void addObjects(const std::shared_ptr<Object> objectToAdd);

	// Utilities
	const std::vector<Intersection> intersectWorld(const Ray& ray) const;
	const Colour shadeHit(const Computation& computation, const int remaining = 4) const;
	const Colour colourAt(const Ray& ray, const int remaining = 4) const;
	bool isShadowed(const Point& point) const;
	const Colour reflectedColour(const Computation& comps, const int remaining = 4) const;
	const Colour refractedColour(const Computation& comps, const int remaining = 4) const;
private:
	std::vector<std::shared_ptr<class Object>> objects;
	std::unique_ptr<class PointLight> light;
	std::unique_ptr<Object> utilObject;
};

