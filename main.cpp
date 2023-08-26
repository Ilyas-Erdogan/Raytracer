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
#include "Primitives/Cube.h"
#include "Primitives/Cylinder.h"
#include "Primitives/Cone.h"
#include <chrono>
#include <utility>
#include <thread>


int main()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;

	World w(false);

	Camera camera(1000, 500, 1.22173);
	camera.setTransform(ViewTransform(Point(-4, 3, 5), Point(0, 0, 0), Vector(0, 1, 0)));

	PointLight light(Point(-1.6, 3, 1), Colour(1, 1, 1));
	w.setLight(light);
	

	// FLOOR
	std::shared_ptr<Object> floor = std::make_shared<Plane>();
	std::shared_ptr<Material> floorMaterial = std::make_shared<Material>();
	std::shared_ptr<Pattern> floorPattern = std::make_shared<CheckersPattern>(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
	floorPattern->setPatternTransform(Scale(0.4, 0.4, 0.4));
	floorMaterial->setPattern(floorPattern);
	floorMaterial->setSpecular(0);
	floorMaterial->setReflectivity(0);
	floor->setMaterial(floorMaterial);
	w.addObjects(floor);

	// RING PATTERN
	std::shared_ptr<Cylinder> ringOne = std::make_shared<Cylinder>(0, 1, true);
	ringOne->setTransform(Translation(0, 0, -2) * Scale(0.5, 1.0, 0.5));
	ringOne->getMaterial()->setColour(Colour(1.0, 0.8, 0.7961));
	w.addObjects(ringOne);

	std::shared_ptr<Cylinder> ringTwo = std::make_shared<Cylinder>(0, 0.8, false);
	ringTwo->setTransform(Translation(0, 0, -2) * Scale(1.0, 1.0, 1.0));
	ringTwo->getMaterial()->setColour(Colour(1, 1, 0));
	w.addObjects(ringTwo);

	std::shared_ptr<Cylinder> ringThree = std::make_shared<Cylinder>(0, 0.6, false);
	ringThree->setTransform(Translation(0, 0, -2) * Scale(1.5, 1.0, 1.5));
	ringThree->getMaterial()->setColour(Colour(1, 1, 0));
	w.addObjects(ringThree);
	
	std::shared_ptr<Cylinder> ringFour = std::make_shared<Cylinder>(0, 0.4, false);
	ringFour->setTransform(Translation(0, 0, -2) * Scale(2.0, 1.0, 2.0));
	ringFour->getMaterial()->setColour(Colour(1, 1, 0));
	w.addObjects(ringFour);

	// Tower
	std::shared_ptr<Cylinder> towerBase = std::make_shared<Cylinder>(0, 1, false);
	towerBase->setTransform(Scale(0.6, 1, 0.6) * Translation(0, 0, 4));
	std::shared_ptr<Pattern> towerPattern = std::make_shared<StripedPattern>(Colour(1, 0, 0), Colour(1, 1, 1));
	towerPattern->setPatternTransform(Scale(0.2, 0.2, 0.2));
	towerBase->getMaterial()->setPattern(towerPattern);
	w.addObjects(towerBase);
	std::shared_ptr<Cone> cone = std::make_shared<Cone>(0, 1, false);
	std::shared_ptr<Pattern> conePattern = std::make_shared<CheckersPattern>(Colour(1, 0, 0), Colour(1, 1, 1));
	conePattern->setPatternTransform(Scale(0.2, 0.2, 0.2));
	cone->getMaterial()->setPattern(conePattern);
	cone->setTransform(Scale(0.8, 1, 0.8) * Translation(0, 2, 3)  * RotationX(PI));
	w.addObjects(cone);

	Canvas canvas = camera.render(w);

	canvas.convertToPPM("Cylinders");

	return 0;
}