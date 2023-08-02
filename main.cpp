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
#include <chrono>
#include <utility>
#include <map>


int main()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;

	std::shared_ptr<Sphere> floor = std::make_shared<Sphere>();
	floor->setTransform(Scale(10, 0.01, 10));
	std::shared_ptr<Material> material = std::make_shared<Material>();
	material->setColour(Colour(1, 0.9, 0.9));
	material->setSpecular(0);
	floor->setMaterial(material);

	std::shared_ptr<Sphere> leftWall = std::make_shared<Sphere>();
	leftWall->setTransform(Translation(0, 0, 5) * RotationY(-PI / 4) * RotationX(PI / 2) * Scale(10, 0.01, 10));
	leftWall->setMaterial(material);

	std::shared_ptr<Sphere> rightWall = std::make_shared<Sphere>();
	rightWall->setTransform(Translation(0, 0, 5) * RotationY(PI / 4) * RotationX(PI / 2) * Scale(10, 0.1, 10));
	rightWall->setMaterial(material);

	std::shared_ptr<Sphere> middle = std::make_shared<Sphere>();
	middle->setTransform(Translation(-0.5, 1, 0.5));
	std::shared_ptr<Material> largeMaterial = std::make_shared<Material>();
	largeMaterial->setColour(Colour(0.1, 1, 0.5));
	largeMaterial->setDiffuse(0.7);
	largeMaterial->setSpecular(0.3);
	middle->setMaterial(largeMaterial);

	std::shared_ptr<Sphere> right = std::make_shared<Sphere>();
	right->setTransform(Translation(1.5, 0.5, -0.5) * Scale(0.5, 0.25, 0.5));
	std::shared_ptr<Material> rightMaterial = std::make_shared<Material>();
	rightMaterial->setColour(Colour(0.5, 1, 0.1));
	rightMaterial->setDiffuse(0.7);
	rightMaterial->setSpecular(0.3);
	right->setMaterial(rightMaterial);

	std::shared_ptr<Sphere> left = std::make_shared<Sphere>();
	left->setTransform(Translation(-1.5, 0.33, -0.75) * Scale(0.33, 0.33, 0.33));
	std::shared_ptr<Material> leftMaterial = std::make_shared<Material>();
	leftMaterial->setColour(Colour(1, 0.8, 0.1));
	leftMaterial->setDiffuse(0.7);
	leftMaterial->setSpecular(0.3);
	left->setMaterial(leftMaterial);

	World w(false);
	w.setLight(PointLight(Point(-10, 10, -10), Colour(1, 1, 1)));
	w.addObjects(floor);
	w.addObjects(leftWall);
	w.addObjects(rightWall);
	w.addObjects(middle);
	w.addObjects(right);
	w.addObjects(left);
	
	Camera camera(1000, 500, PI / 3);
	camera.setTransform(ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));
	Canvas canvas = camera.render(w);

	canvas.convertToPPM("Scene");
	return 0;
}