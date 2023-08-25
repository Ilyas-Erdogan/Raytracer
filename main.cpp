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
#include "Cube.h"
#include <chrono>
#include <utility>
#include <thread>


int main()
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209;

	World w(false);

	Camera camera(1000, 500, 0.785);
	camera.setTransform(ViewTransform(Point(8, 6, -8), Point(0, 3, 0), Vector(0, 1, 0)));

	w.setLight(PointLight(Point(0, 6.9, -5), Colour(1, 1, 0.9)));

	// FLOOR/CEILING
	std::shared_ptr<Object> floor = std::make_shared<Cube>();
	floor->setTransform(Scale(20, 7, 20) * Translation(0, 1, 0));
	std::shared_ptr<Material> floorMaterial = std::make_shared<Material>();
	std::shared_ptr<Pattern> floorPattern = std::make_shared<CheckersPattern>(Colour(0, 0, 0), Colour(0.25, 0.25, 0.25));
	floorPattern->setPatternTransform(Scale(0.07, 0.07, 0.07));
	floorMaterial->setPattern(floorPattern);
	floorMaterial->setAmbient(0.25);
	floorMaterial->setDiffuse(0.7);
	floorMaterial->setSpecular(0.9);
	floorMaterial->setShininess(300);
	floorMaterial->setReflectivity(0.1);
	floor->setMaterial(floorMaterial);

	// WALLS
	std::shared_ptr<Object> wall = std::make_shared<Cube>();
	wall->setTransform(Scale(10, 10, 10));
	std::shared_ptr<Material> wallMaterial = std::make_shared<Material>();
	std::shared_ptr<Pattern> wallPattern = std::make_shared<CheckersPattern>(Colour(0.4863, 0.3765, 0.2941), Colour(0.3725, 0.2902, 0.2275));
	wallPattern->setPatternTransform(Scale(0.05, 0.05, 0.05));
	wallMaterial->setPattern(wallPattern);
	wallMaterial->setAmbient(0.1);
	wallMaterial->setDiffuse(0.7);
	wallMaterial->setSpecular(0.9);
	wallMaterial->setShininess(300);
	wallMaterial->setReflectivity(0.1);
	wall->setMaterial(wallMaterial);

	// TABLE TOP
	std::shared_ptr<Object> top = std::make_shared<Cube>();
	top->setTransform(Translation(0, 3.1, 0) * Scale(3, 0.1, 2));
	std::shared_ptr<Material> topMaterial = std::make_shared<Material>();
	std::shared_ptr<Pattern> topPattern = std::make_shared<StripedPattern>(Colour(0.5529, 0.4235, 0.3255), Colour(0.6588, 0.5098, 0.4000));
	topPattern->setPatternTransform(Scale(0.05, 0.05, 0.05) * RotationY(0.1));
	topMaterial->setPattern(topPattern);
	topMaterial->setAmbient(0.1);
	topMaterial->setDiffuse(0.7);
	topMaterial->setSpecular(0.9);
	topMaterial->setShininess(300);
	topMaterial->setReflectivity(0.2);
	top->setMaterial(topMaterial);
	

	// LEG MATERIAL
	std::shared_ptr<Material> legMaterial = std::make_shared<Material>();
	legMaterial->setColour(Colour(0.5529, 0.4235, 0.3255));
	legMaterial->setAmbient(0.2);
	legMaterial->setDiffuse(0.7);

	// LEG 1
	std::shared_ptr<Object> legOne = std::make_shared<Cube>();
	legOne->setTransform(Translation(2.7, 1.5, -1.7) * Scale(0.1, 1.5, 0.1));
	legOne->setMaterial(legMaterial);
	
	// LEG 2
	std::shared_ptr<Object> legTwo = std::make_shared<Cube>();
	legTwo->setTransform(Translation(2.7, 1.5, 1.7) * Scale(0.1, 1.5, 0.1));
	legTwo->setMaterial(legMaterial);

	// LEG 3
	std::shared_ptr<Object> legThree = std::make_shared<Cube>();
	legThree->setTransform(Translation(-2.7, 1.5, -1.7) * Scale(0.1, 1.5, 0.1));
	legThree->setMaterial(legMaterial);

	// LEG 4
	std::shared_ptr<Object> legFour = std::make_shared<Cube>();
	legFour->setTransform(Translation(-2.7, 1.5, 1.7) * Scale(0.1, 1.5, 0.1));
	legFour->setMaterial(legMaterial);

	// GLASS CUBE
	std::shared_ptr<Object> glassCube = std::make_shared<Cube>();
	glassCube->setTransform(Translation(0, 3.45001, 0) * RotationY(0.2) * Scale(0.25, 0.25, 0.25));
	std::shared_ptr<Material> glassCubeMaterial = std::make_shared<Material>(Colour(1, 1, 0.8), 0, 0.3, 0.9, 300, 0.7, 0.7, 1.5);
	glassCube->setMaterial(glassCubeMaterial);

	// LITTLE CUBE ONE
	std::shared_ptr<Object> littleCubeOne = std::make_shared<Cube>();
	littleCubeOne->setTransform(Translation(1, 3.35, -0.9) * RotationY(-0.4) * Scale(0.15, 0.15, 0.15));
	std::shared_ptr<Material> littleMaterialOne = std::make_shared<Material>();
	littleMaterialOne->setColour(Colour(1, 0.5, 0.5));
	littleMaterialOne->setReflectivity(0.6);
	littleMaterialOne->setDiffuse(0.4);
	littleCubeOne->setMaterial(littleMaterialOne);

	// LITTLE CUBE TWO 
	std::shared_ptr<Object> littleCubeTwo = std::make_shared<Cube>();
	littleCubeTwo->setTransform(Translation(-1.5, 3.27, 0.3) * RotationY(0.4) * Scale(0.15, 0.07, 0.15));
	std::shared_ptr<Material> littleMaterialTwo = std::make_shared<Material>();
	littleMaterialTwo->setColour(Colour(1, 1, 0.5));
	littleCubeTwo->setMaterial(littleMaterialTwo);
	
	// LITTLE CUBE THREE
	std::shared_ptr<Object> littleCubeThree = std::make_shared<Cube>();
	littleCubeThree->setTransform(Translation(0, 3.25, 1) * RotationY(0.4) * Scale(0.2, 0.05, 0.05));
	std::shared_ptr<Material> littleMaterialThree = std::make_shared<Material>();
	littleMaterialThree->setColour(Colour(0.5, 1, 0.5));
	littleCubeThree->setMaterial(littleMaterialThree);

	// LITTLE CUBE FOUR
	std::shared_ptr<Object> littleCubeFour = std::make_shared<Cube>();
	littleCubeFour->setTransform(Translation(-0.6, 3.4, -1)* RotationY(0.8)* Scale(0.05, 0.2, 0.05));
	std::shared_ptr<Material> littleMaterialFour = std::make_shared<Material>();
	littleMaterialFour->setColour(Colour(0.5, 0.5, 1));
	littleCubeFour->setMaterial(littleMaterialFour);

	// LITTLE CUBE FIVE
	std::shared_ptr<Object> littleCubeFive = std::make_shared<Cube>();
	littleCubeFive->setTransform(Translation(2, 3.4, 1)* RotationY(0.8)* Scale(0.05, 0.2, 0.05));
	std::shared_ptr<Material> littleMaterialFive = std::make_shared<Material>();
	littleMaterialFour->setColour(Colour(0.5, 1, 1));
	littleCubeFive->setMaterial(littleMaterialFive);

	// FRAME ONE
	std::shared_ptr<Object> frameOne = std::make_shared<Cube>();
	frameOne->setTransform(Translation(-10, 4, 1)* Scale(0.05, 1, 1));
	std::shared_ptr<Material> frameOneMaterial = std::make_shared<Material>();
	frameOneMaterial->setColour(Colour(0.7098, 0.2471, 0.2196));
	frameOneMaterial->setDiffuse(0.6);
	frameOne->setMaterial(frameOneMaterial);

	// FRAME TWO
	std::shared_ptr<Object> frameTwo = std::make_shared<Cube>();
	frameTwo->setTransform(Translation(-10, 3.4, 2.7)* Scale(0.05, 0.4, 0.4));
	std::shared_ptr<Material> frameTwoMaterial = std::make_shared<Material>();
	frameTwoMaterial->setColour(Colour(0.2667, 0.2706, 0.6902));
	frameTwoMaterial->setDiffuse(0.6);
	frameTwo->setMaterial(frameTwoMaterial);

	// FRAME THREE
	std::shared_ptr<Object> frameThree = std::make_shared<Cube>();
	frameThree->setTransform(Translation(-10, 4.6, 2.7)* Scale(0.05, 0.4, 0.4));
	std::shared_ptr<Material> frameThreeMaterial = std::make_shared<Material>();
	frameThreeMaterial->setColour(Colour(0.3098, 0.5961, 0.3098));
	frameThreeMaterial->setDiffuse(0.6);
	frameThree->setMaterial(frameThreeMaterial);

	// MIRROR FRAME
	std::shared_ptr<Object> mirrorFrame = std::make_shared<Cube>();
	mirrorFrame->setTransform(Translation(-2, 3.5, 9.95)* Scale(5, 1.5, 0.05));
	std::shared_ptr<Material> mirrorFrameMaterial = std::make_shared<Material>();
	mirrorFrameMaterial->setColour(Colour(0.3882, 0.2627, 0.1882));
	mirrorFrameMaterial->setDiffuse(0.7);
	mirrorFrame->setMaterial(mirrorFrameMaterial);

	// MIRROR
	std::shared_ptr<Object> mirror = std::make_shared<Cube>();
	mirror->setTransform(Translation(-2, 3.5, 9.95)* Scale(4.8, 1.4, 0.06));
	std::shared_ptr<Material> mirrorMaterial = std::make_shared<Material>();
	mirrorMaterial->setColour(Colour(0, 0, 0));
	mirrorMaterial->setDiffuse(0);
	mirrorMaterial->setAmbient(0);
	mirrorMaterial->setSpecular(1);
	mirrorMaterial->setShininess(300);
	mirrorMaterial->setReflectivity(1);
	mirror->setMaterial(mirrorMaterial);

	w.addObjects(floor);
	w.addObjects(wall);
	w.addObjects(top);
	w.addObjects(legOne);
	w.addObjects(legTwo);
	w.addObjects(legThree);
	w.addObjects(legFour);
	w.addObjects(glassCube);
	w.addObjects(littleCubeOne);
	w.addObjects(littleCubeTwo);
	w.addObjects(littleCubeThree);
	w.addObjects(littleCubeFour);
	w.addObjects(littleCubeFive);
	w.addObjects(frameOne);
	w.addObjects(frameTwo);
	w.addObjects(frameThree);
	w.addObjects(mirrorFrame);
	w.addObjects(mirror);

	Canvas canvas = camera.render(w);

	canvas.convertToPPM("TableScene");

	return 0;
}