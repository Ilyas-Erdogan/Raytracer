#include "World.h"
#include "PointLight.h"
#include "Primitives/Sphere.h"
#include "Transformations/Scale.h"
#include <algorithm>
#include <cmath>

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
const std::vector<std::shared_ptr<class Object>>& World::getObjects() const
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
void World::addObjects(const std::shared_ptr<Object> objectToAdd)
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
	for (auto &objectsI : this->objects)
	{
		for (auto& intersects : objectsI->intersect(ray))
		{
			intersections.emplace_back(intersects);
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
const Colour World::shadeHit(const Computation& computation, const int remaining)
{
	Colour surface = computation.getObject()->getMaterial()->lighting(computation.getObject(), this->getLightSource(), computation.getOverPoint(), computation.getEyeV(), computation.getNormalV(), this->isShadowed(computation.getOverPoint()));
	Colour reflected = this->reflectedColour(computation, remaining);
	Colour refracted = this->refractedColour(computation, remaining);
	
	std::shared_ptr<Material> material = computation.getObject()->getMaterial();
	//printf("%f %f\n", material->getReflectivity(), material->getTransparency());

	if (material->getReflectivity() > 0.0 && material->getTransparency() > 0.0)
	{
		//printf("N1: %f AND N2: %f\n", computation.getExit(), computation.getEnter());
		double reflectance = computation.schlick();
		//printf("SCHLICK: %f\n", reflectance);
		
		return surface + (reflected * reflectance) + refracted * (1 - reflectance);
	}
	else
	{
		return surface + reflected + refracted;
	}
}

/**
* Determines colour found in the scene determined by the cast ray.
* 
* @param Ray ray Reference to the ray being cast in the scene.
* 
* @return An immutable Colour (to be drawn onto the canvas).
*/
const Colour World::colourAt(const Ray& ray, const int remaining)
{
	// Find intersections with given ray
	std::vector<Intersection> intersections = this->intersectWorld(ray);

	// Find hit from resulting intersections
	std::shared_ptr<Intersection> hitCheck = utilObject->hit(intersections);
	// If no hits are found, return a black colour
	if (hitCheck == nullptr)
	{
		return Colour();
	}
	else
	{
		// Prepare the appropraite computations to be used for shading.
		// Determine Colour to be written.
		return this->shadeHit(hitCheck->prepareComputations(ray, intersections), remaining);
	}
}

/**
* Checks if a point is shadowed.
* 
* @param Point point Reference to the point to use to measure distance from the light source.
* 
* @return True if a hit exists and the t intersection is less than the calcualted distance, otherwise false.
*/
bool World::isShadowed(const Point& point)
{
	// Measure distance from point to the light source
	Vector v = this->getLightSource().getPosition() - point;
	double distance = v.getMagnitude();

	// Create ray from point to the light source
	Vector direction = v.normalizeVector();
	Ray r(point, direction);

	// Intersect the world with the ray
	std::vector<Intersection> intersections = this->intersectWorld(r);
	std::shared_ptr<Intersection> h = utilObject->hit(intersections);
	// Check for hit and if t value is less than distance.
	if (h != nullptr && h->getT() < distance)
	{
		// Hit lies between point and light source
		return true;
	}
	// No hit
	return false;
}

/**
* Determines the colour to display based on the intersected object's reflecitivity attribute.
* 
* @pararm Computation comps Reference to the computation used help with calculations.
* 
* @return The colour to display.
*/
const Colour World::reflectedColour(const Computation& comps, const int remaining)
{
	// Check for no reflectivity
	if (remaining <= 0 || comps.getObject()->getMaterial()->getReflectivity() == 0.0)
	{
		return Colour(0, 0, 0);
	}

	Ray reflectRay(comps.getOverPoint(), comps.getReflectV());
	Colour colour = this->colourAt(reflectRay, remaining - 1);
	return colour * comps.getObject()->getMaterial()->getReflectivity();
}

const Colour World::refractedColour(const Computation& comps, const int remaining)
{
	// Check for lack of transparency (opaque object)
	if (comps.getObject()->getMaterial()->getTransparency() == 0)
	{
		return Colour(0, 0, 0);
	}

	// Apply Snell's law.
	// Find the ratio of the first refraction index to the second.
	double nRatio = comps.getExit() / comps.getEnter();
	// Get the dot product of the two vectors.
	double cosI = comps.getEyeV().dotProduct(comps.getNormalV());
	// Find the sin(thetha_t)^2 using trigonometric identity.
	double sin2T = (nRatio * nRatio) * (1 - cosI * cosI);

	if (sin2T > 1.0)
	{
		return Colour(0, 0, 0);
	}

	// Find cos(theta t) via trig identity
	double cosT = std::sqrt(1.0 - sin2T);
	// Compute the direction of the refracted ray
	Vector direction = comps.getNormalV() * (nRatio * cosI - cosT) - comps.getEyeV() * nRatio;
	// Creat refracted ray
	Ray refractRay(comps.getUnderPoint(), direction);

	// Find the colour of the refracted ray, multiply by transparency to account for opacity
	Colour colour = this->colourAt(refractRay, remaining - 1);
	colour *= comps.getObject()->getMaterial()->getTransparency();
	return colour;
}
