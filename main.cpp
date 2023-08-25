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

	//// Fresnel Effect
	//World w(false);

	//Camera camera(600, 600, 0.45);
	//camera.setTransform(ViewTransform(Point(0, 0, -5), Point(0, 0, 0), Vector(0, 1, 0)));

	//PointLight light(Point(2, 10, -5), Colour(0.9, 0.9, 0.9));
	//w.setLight(light);

	//std::shared_ptr<Object> wall = std::make_shared<Plane>();
	//wall->setTransform(Translation(0, 0, 10) * RotationX(1.5708));
	//std::shared_ptr<Material> wallMaterial = std::make_shared<Material>();
	//std::shared_ptr<Pattern> wallPattern = std::make_shared<CheckersPattern>(Colour(0.15, 0.15, 0.15), Colour(0.85, 0.85, 0.85));
	//wallMaterial->setPattern(wallPattern);
	//wallMaterial->setAmbient(0.8);
	//wallMaterial->setDiffuse(0.2);
	//wallMaterial->setSpecular(0);
	//wall->setMaterial(wallMaterial);
	//w.addObjects(wall);

	//std::shared_ptr<Object> ball = std::make_shared<Sphere>();
	//std::shared_ptr<Material> ballMaterial = std::make_shared<Material>(Colour(1, 1, 1), 0, 0, 0.9, 300, 0.9, 0.9, 1.5);
	////ballMaterial->setPattern(std::make_shared<Pattern>(Colour(0, 0, 0), Colour(1, 1, 1)));
	//ball->setMaterial(ballMaterial);
	//w.addObjects(ball);
	// 
	//std::shared_ptr<Object> hollow = std::make_shared<Sphere>();
	//hollow->setTransform(Scale(0.5, 0.5, 0.5));
	//std::shared_ptr<Material> hollowMaterial = std::make_shared<Material>(Colour(1, 1, 1), 0, 0, 0.9, 300, 0.9, 0.9, 1.000273);
	////hollowMaterial->setPattern(std::make_shared<Pattern>(Colour(0, 0, 0), Colour(1, 1, 1)));
	//hollow->setMaterial(hollowMaterial);
	//w.addObjects(hollow);

	//Canvas canvas = camera.render(w);

	//canvas.convertToPPM("FresnelTest");


	// Refraction/Reflection Scene
	World w(false);

	Camera camera(800, 400, 1.152);
	camera.setTransform(ViewTransform(Point(-2.6, 1.5, -3.9), Point(-0.6, 1, -0.8), Vector(0, 1, 0)));

	PointLight light(Point(-4.9, 4.9, -1), Colour(1, 1, 1));
	w.setLight(light);

	// WALL
	std::shared_ptr<Pattern> wallPattern = std::make_shared<StripedPattern>(Colour(0.45, 0.45, 0.45), Colour(0.55, 0.55, 0.55));
	wallPattern->setPatternTransform(RotationY(1.5708) * Scale(0.25, 0.25, 0.25));
	std::shared_ptr<Material> wallMaterial = std::make_shared<Material>();
	wallMaterial->setPattern(wallPattern);
	wallMaterial->setAmbient(0);
	wallMaterial->setDiffuse(0.4);
	wallMaterial->setSpecular(0);
	wallMaterial->setReflectivity(0.3);

	// FLOOR
	std::shared_ptr<Object> floor = std::make_shared<Plane>();
	floor->setTransform(RotationY(0.31415));
	std::shared_ptr<Material> floorMaterial = std::make_shared<Material>();
	std::shared_ptr<Pattern> floorPattern = std::make_shared<CheckersPattern>(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
	floorMaterial->setPattern(floorPattern);
	floorMaterial->setSpecular(0);
	floorMaterial->setReflectivity(0.4);
	floor->setMaterial(floorMaterial);
	w.addObjects(floor);

	// CEILING
	std::shared_ptr<Object> ceiling = std::make_shared<Plane>();
	ceiling->setTransform(Translation(0, 5, 0));
	std::shared_ptr<Material> ceilingMaterial = std::make_shared<Material>();
	ceilingMaterial->setColour(Colour(0.8, 0.8, 0.8));
	ceilingMaterial->setAmbient(0.3);
	ceilingMaterial->setSpecular(0);
	ceiling->setMaterial(ceilingMaterial);
	w.addObjects(ceiling);

	// WEST WALL
	std::shared_ptr<Object> westWall = std::make_shared<Plane>();
	westWall->setTransform(Translation(-5, 0, 0) * RotationZ(1.5708) * RotationY(1.5708));
	westWall->setMaterial(wallMaterial);
	w.addObjects(westWall);

	// EAST WALL
	std::shared_ptr<Object> eastWall = std::make_shared<Plane>();
	eastWall->setTransform(Translation(5, 0, 0) * RotationZ(1.5708) * RotationY(1.5708));
	eastWall->setMaterial(wallMaterial);
	w.addObjects(eastWall);

	// NORTH WALL
	std::shared_ptr<Object> northWall = std::make_shared<Plane>();
	northWall->setTransform(Translation(0, 0, 5) * RotationX(1.5708));
	northWall->setMaterial(wallMaterial);
	w.addObjects(northWall);

	// SOUTH WALL
	std::shared_ptr<Object> southWall = std::make_shared<Plane>();
	southWall->setTransform(Translation(0, 0, -5) * RotationX(1.5708));
	southWall->setMaterial(wallMaterial);
	w.addObjects(southWall);

	// BGBalls
	std::shared_ptr<Object> BGBall1 = std::make_shared<Sphere>();
	BGBall1->setTransform(Translation(4.6, 0.4, 1) * Scale(0.4, 0.4, 0.4));
	std::shared_ptr<Material> BGMaterial1 = std::make_shared<Material>();
	BGMaterial1->setColour(Colour(0.8, 0.5, 0.3));
	BGMaterial1->setShininess(50);
	BGBall1->setMaterial(BGMaterial1);
	w.addObjects(BGBall1);

	std::shared_ptr<Object> BGBall2 = std::make_shared<Sphere>();
	BGBall2->setTransform(Translation(4.7, 0.3, 0.4) * Scale(0.3, 0.3, 0.3));
	std::shared_ptr<Material> BGMaterial2 = std::make_shared<Material>();
	BGMaterial2->setColour(Colour(0.9, 0.4, 0.5));
	BGMaterial2->setShininess(50);
	BGBall2->setMaterial(BGMaterial2);
	w.addObjects(BGBall2);

	std::shared_ptr<Object> BGBall3 = std::make_shared<Sphere>();
	BGBall3->setTransform(Translation(-1, 0.5, 4.5) * Scale(0.5, 0.5, 0.5));
	std::shared_ptr<Material> BGMaterial3 = std::make_shared<Material>();
	BGMaterial3->setColour(Colour(0.4, 0.9, 0.6));
	BGMaterial3->setShininess(50);
	BGBall3->setMaterial(BGMaterial3);
	w.addObjects(BGBall3);

	std::shared_ptr<Object> BGBall4 = std::make_shared<Sphere>();
	BGBall4->setTransform(Translation(-1.7, 0.3, 4.7) * Scale(0.3, 0.3, 0.3));
	std::shared_ptr<Material> BGMaterial4 = std::make_shared<Material>();
	BGMaterial4->setColour(Colour(0.4, 0.6, 0.9));
	BGMaterial4->setShininess(50);
	BGBall4->setMaterial(BGMaterial4);
	w.addObjects(BGBall4);

	// FGBalls
	std::shared_ptr<Object> FGBall1 = std::make_shared<Sphere>();
	FGBall1->setTransform(Translation(-0.6, 1, 0.6));
	std::shared_ptr<Material> FGMaterial1 = std::make_shared<Material>();
	FGMaterial1->setColour(Colour(1, 0.3, 0.2));
	FGMaterial1->setSpecular(0.4);
	FGMaterial1->setShininess(5);
	FGBall1->setMaterial(FGMaterial1);
	w.addObjects(FGBall1);

	std::shared_ptr<Object> FGBall2 = std::make_shared<Sphere>();
	FGBall2->setTransform(Translation(0.6, 0.7, -0.6) * Scale(0.7, 0.7 ,0.7));
	std::shared_ptr<Material> FGMaterial2 = std::make_shared<Material>(Colour(0, 0, 0.2), 0, 0.4, 0.9, 300, 0.9, 0.9, 1.52);
	FGBall2->setMaterial(FGMaterial2);
	w.addObjects(FGBall2);
	std::cout << FGBall2->getMaterial()->getRefractiveIndex() << std::endl;

	std::shared_ptr<Object> FGBall3 = std::make_shared<Sphere>();
	FGBall3->setTransform(Translation(-0.7, 0.5, -0.8) * Scale(0.5, 0.5, 0.5));
	std::shared_ptr<Material> FGMaterial3 = std::make_shared<Material>(Colour(0, 0.2, 0), 0, 0.4, 0.9, 300, 0.9, 0.9, 1.52);
	FGBall3->setMaterial(FGMaterial3);
	w.addObjects(FGBall3);
	std::cout << FGBall3->getMaterial()->getRefractiveIndex() << std::endl;

	Canvas canvas = camera.render(w);

	canvas.convertToPPM("Chapter11Scene");

	return 0;
}