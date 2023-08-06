#include <iostream>
#include "Types/Vector.h"
#include "Types/Point.h"
#include "Canvas.h"
#include "Types/Colour.h"
#include "Types/Matrix.h"
#include "Transformations/Translation.h"
#include "Transformations/Scale.h"
#include "Transformations/RotationX.h"
#include "Transformations/RotationY.h"
#include "Transformations/RotationZ.h"
#include "Transformations/Shearing.h"
#include "Ray.h"
#include "Primitives/Object.h"
#include "Primitives/Sphere.h"
#include "Types/Intersection.h"
#include "Material.h"
#include "PointLight.h"
#include "World.h"
#include "Camera.h"
#include "Transformations/ViewTransform.h"
#include "Primitives/Plane.h"
#include "Patterns/Pattern.h"
#include "Patterns/StripedPattern.h"
#include "Patterns/GradientPattern.h"
#include "Patterns/RingPattern.h"
#include "Patterns/CheckersPattern.h"
#include <chrono>
#include <utility>
#include <thread>


int main()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;

	// Patterns
	const double MAX = 255.0;
	std::shared_ptr<Pattern> floorPattern = std::make_shared<CheckersPattern>(Colour(38.0/MAX, 38.0 / MAX, 38.0 / MAX), Colour(181.0/MAX, 181.0 / MAX, 181.0 / MAX));
	std::shared_ptr<Pattern> wallPattern = std::make_shared<StripedPattern>(Colour(38.0 / MAX, 38.0 / MAX, 38.0 / MAX), Colour(181.0 / MAX, 181.0 / MAX, 181.0 / MAX));
	wallPattern->setPatternTransform(Scale(0.9, 0.9, 0.9) * RotationY(PI/9));
	std::shared_ptr<Pattern> leftSpherePattern = std::make_shared<RingPattern>(Colour(111.0/MAX, 255.0/MAX, 111.0/MAX), Colour(0, 166.0 / MAX, 0));
	leftSpherePattern->setPatternTransform(Scale(0.2, 0.2, 0.2));
	std::shared_ptr<Pattern> rightSpherePattern = std::make_shared<GradientPattern>(Colour(1.0, 165/MAX, 0), Colour(1, 0, 0));
	rightSpherePattern->setPatternTransform(Translation(-1, 0, 0) * Scale(2, 1, 1));

	// Floor
	std::shared_ptr<Object> floor = std::make_shared<Plane>();
	std::shared_ptr<Material> floorMaterial = std::make_shared<Material>();
	floorMaterial->setPattern(floorPattern);
	floor->setMaterial(floorMaterial);

	// Wall
	std::shared_ptr<Object> wall = std::make_shared<Plane>();
	wall->setTransform(Translation(0, 0, 5) * RotationX(PI / 2) );
	std::shared_ptr<Material> wallMaterial = std::make_shared<Material>();
	wallMaterial->setPattern(wallPattern);
	wall->setMaterial(wallMaterial);

	// Big Sphere
	std::shared_ptr<Object> bigSphere = std::make_shared<Sphere>();
	bigSphere->setTransform(Translation(-1, 1, 1.5) * RotationY(PI / 8) * RotationX(-PI / 2.5));
	std::shared_ptr<Material> bigSphereMaterial = std::make_shared<Material>();
	bigSphereMaterial->setPattern(leftSpherePattern);
	bigSphere->setMaterial(bigSphereMaterial);

	// Small Sphere
	std::shared_ptr<Object> smallSphere = std::make_shared<Sphere>();
	smallSphere->setTransform(Translation(1, 0.5, 1) * Scale(0.5, 0.5, 0.5));
	std::shared_ptr<Material> smallSphereMaterial = std::make_shared<Material>();
	smallSphereMaterial->setPattern(rightSpherePattern);
	smallSphere->setMaterial(smallSphereMaterial);

	World w(false);
	w.setLight(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
	w.addObjects(floor);
	w.addObjects(wall);
	w.addObjects(bigSphere);
	w.addObjects(smallSphere);
	
	Camera camera(2000, 1000, PI / 3);
	camera.setTransform(ViewTransform(Point(0, 1.5, -5), Point(0, 1.0, -0.5), Vector(0, 1, 0)));

	Canvas canvas = camera.render(w);

	canvas.convertToPPM("PatternsScene");
	return 0;
}