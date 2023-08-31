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
#include "Primitives/Group.h"
#include "Primitives/Triangle.h"
#include "Parser.h"
#include <chrono>
#include <utility>
#include <thread>


std::shared_ptr<Sphere> hexagonCorner()
{
	std::shared_ptr<Sphere> corner = std::make_shared<Sphere>();
	corner->setTransform(Translation(0, 0, -1) * Scale(0.25, 0.25, 0.25));

	return corner;
}

std::shared_ptr<Cylinder> hexagonEdge()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;
	std::shared_ptr<Cylinder> edge = std::make_shared<Cylinder>(0, 1);
	edge->setTransform(Translation(0, 0, -1) * RotationY(-PI / 6) * RotationZ(-PI / 2) * Scale(0.25, 1, 0.25));
	
	return edge;
}

std::shared_ptr<Group> hexagonSide()
{
	std::shared_ptr<Group> side = std::make_shared<Group>();
	side->addChild(hexagonCorner());
	side->addChild(hexagonEdge());

	return side;
}

std::shared_ptr<Group> hexagon()
{
	std::shared_ptr<Group> hex = std::make_shared<Group>();
	for (int n = 0; n <= 5; n++)
	{
		const double PI = 3.1415926535897932384626433832795028841971693993751058209;
		std::shared_ptr<Group> side = hexagonSide();
		side->setTransform(RotationY(n * PI / 3));
		hex->addChild(side);
	}

	return hex;
}

int main()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;
	//World w(false);

	//Camera camera(1000, 500, 1.22173);
	//camera.setTransform(ViewTransform(Point(-4, 3, 5), Point(0, 0, 0), Vector(0, 1, 0)));

	//PointLight light(Point(-1.6, 3, 1), Colour(1, 1, 1));
	//w.setLight(light);
	//
	//std::shared_ptr<Group> hex = hexagon();
	////std::shared_ptr<Material> mat = std::make_shared<Material>(Colour(1, 0, 0));
	////hex->getMaterial()->setColour(Colour(0, 1, 0));
	//hex->getMaterial()->setRefractiveIndex(1.52);
	////hex->addChild(hexagon());
	//hex->setTransform(Translation(0, 0.5, 0));

	//w.addObjects(hex);


	//// FLOOR
	//std::shared_ptr<Object> floor = std::make_shared<Plane>();
	//floor->setTransform(RotationY(0.31415));
	//std::shared_ptr<Material> floorMaterial = std::make_shared<Material>();
	//std::shared_ptr<Pattern> floorPattern = std::make_shared<CheckersPattern>(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
	//floorMaterial->setPattern(floorPattern);
	//floorMaterial->setSpecular(0);
	//floorMaterial->setReflectivity(0.4);
	//floor->setMaterial(floorMaterial);
	//w.addObjects(floor);

	//Canvas canvas = camera.render(w);

	//canvas.convertToPPM("Hexagon1");

	World w(false);

	Camera camera(100, 50, 1.22173);
	camera.setTransform(ViewTransform(Point(-4, 2, 0), Point(0, 1, 0), Vector(0, 1, 0)));

	PointLight light(Point(-5, 5, -7), Colour(1, 1, 1));
	w.setLight(light);

	Parser parser("pumpkin.txt");
	std::shared_ptr<Group> astro = parser.objToGroup();
	astro->setTransform(Translation(2, 5, 0) * Scale(0.0004, 0.0004, 0.0004) * RotationX(-PI / 2));
	astro->getMaterial()->setColour(Colour(1, 0.647, 0));
	w.addObjects(astro);
	//w.addObjects(std::make_shared<Sphere>());

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

	std::shared_ptr<Object> object = std::make_shared<Sphere>();
	object->setTransform(Translation(0, 1, 0));
	//w.addObjects(object);

	Canvas canvas = camera.render(w);

	canvas.convertToPPM("atsro");
	int n;
	//std::cin >> n;


	return 0;
}