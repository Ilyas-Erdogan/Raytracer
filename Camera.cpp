#include "Camera.h"
#include <cmath>
#include <chrono>
#include <utility>
#include <thread>

/**
* Constrcuts a virtual "camera" that can "take pictures" of the scene.
* 
* @param double horizontalSize The horizontal size in pixels of the canvas.
* @param double verticalSize The vertical size in pixels of the canvas.
* @param double fieldOfViewVal The angle that describes the how much the camera can see.
*/
Camera::Camera(const double horizontalSize, const double verticalSize, const double fieldOfViewVal)
	: transform{ Matrix(4, 4).getIdentityMatrix()}, hSize{horizontalSize}, vSize{verticalSize}, fieldOfView{fieldOfViewVal}
{
	// Assumes canvas is one unit away.
	double halfView = std::tan(this->fieldOfView / 2); // Width of hald the canvas.
	double aspect = this->hSize / this->vSize; // Aspect ration of horizontal size to vertical size.
	// If vertical size is greater (or equal) than the horizontal then,
	if (aspect >= 1.0)
	{
		// The halfview should be half the width.
		this->halfWidth = halfView;
		this->halfHeight = halfView / aspect;
	}
	else
	{
		// The halfview should be half the height.
		this->halfWidth = halfView * aspect;
		this->halfHeight = halfView;
	}

	// Set pixel size in accordance to calculated values.
	this->pixelSize = (halfWidth * 2) / this->hSize;
	
	// Set cached inverse transform
	this->inverseTransform = this->transform;
}

Camera::~Camera()
{
}

/**
* @return The horizontal size of the canvas.
*/
double Camera::getHorizontalSize() const
{
	return this->hSize;
}

/**
* @return The vertical size of the canvas.
*/
double Camera::getVerticalSize() const
{
	return this->vSize;
}

/**
* @return The field of view (angle) of the camera.
*/
double Camera::getFieldOfView() const
{
	return this->fieldOfView;
}

/**
* An immutable reference to transformation matrix of the camera.
*/
const Matrix& Camera::getTransform() const
{
	return this->transform;
}

/**
* An immutable reference to the inverse transformation matrix of the camera.
*/
const Matrix& Camera::getInverseTransform() const
{
	return this->inverseTransform;
}

/**
* @param Matrix transformToSet Reference to the transformation Matrix to apply to the camera object.
*/
void Camera::setTransform(const Matrix& transformToSet)
{
	this->transform = transformToSet;
	this->inverseTransform = transformToSet.getInverse();
}

/**
* @return The calculated size of a single pixel.
*/
double Camera::getPixelSize() const
{
	return this->pixelSize;
}

/**
* Returns a new ray that starts at the camera and passes through the provided coordinates.
* 
* @param int pX The x-coordinate to be passed through.
* @param int pY The y-coordinated to be passed through.
* 
* @return A new Ray object according to given parameters.
*/
const Ray Camera::rayForPixel(const int pX, const int pY) const
{
	// The offset from teh edge of the canvas to the pixel's center
	double xOffset = (pX + 0.5) * this->pixelSize;
	double yOffset = (pY + 0.5) * this->pixelSize;

	// The untransformed coordinates of the pixel in the world space
	double worldX = this->halfWidth - xOffset;
	double worldY = this->halfHeight - yOffset;

	// Using camera matrix, transform the canvas point and origin, and compute ray's direction vector
	Point pixel = this->getInverseTransform() * Point(worldX, worldY, -1);
	Point origin = this->getInverseTransform() * Point(0, 0, 0);
	Vector direction = (pixel - origin).normalizeVector();

	return Ray(origin, direction);

}

/**
* Renders a canvas using the calling object (camera) to render an image of the given world.
*
* @param @World world Reference to the world to be draw to teh canvas.
*
* @return A canvas containing the rendered image.
*/
Canvas Camera::render(World& world) const
{
	Canvas image(this->hSize, this->vSize, Colour());

	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::nanoseconds elapsed;
	std::chrono::nanoseconds sum = std::chrono::nanoseconds::zero();
	#pragma omp parallel for
	for (int y = 0; y < static_cast<int>(this->vSize); y++)
	{
		begin = std::chrono::high_resolution_clock::now();
		for (int x = 0; x < static_cast<int>(this->hSize); x++)
		{
			Ray r(this->rayForPixel(x, y));
			Colour colour = world.colourAt(r);
			image.writePixel(x, y, colour);
			//printf("Time measured: %.3f seconds.\n", sum.count() * 1e-9);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		sum += elapsed;
		printf("Time measured: %.3f seconds. %i // %i\n", sum.count() * 1e-9, y, static_cast<int>(this->vSize));
	}
	printf("Time measured: %.3f seconds.\n", sum.count() * 1e-9);
	printf("FINI");

	return image;
}

///**
//* Renders a canvas using the calling object (camera) to render an image of the given world.
//* 
//* @param @World world Reference to the world to be draw to teh canvas.
//* 
//* @return A canvas containing the rendered image.
//*/
//const Canvas Camera::render(World& world) const
//{
//	std::vector<Colour> section = {};
//	const std::pair<int, int> pairOne = std::make_pair<int, int>(0, this->vSize * 0.25);
//	const std::pair<int, int> pairTwo = std::make_pair<int, int>(this->vSize/4 * 0.25 + 1, this->vSize * 0.5);
//	const std::pair<int, int> pairThree = std::make_pair<int, int>(this->vSize * 0.5 + 1, this->vSize * 0.75);
//	const std::pair<int, int> pairFour = std::make_pair<int, int>(this->vSize * 0.75 + 1, this->vSize);
//
//	std::vector<Colour> calcOne;
//	std::vector<Colour> calcTwo;
//	std::vector<Colour> calcThree;
//	std::vector<Colour> calcFour;
//
//	std::thread t1(&Camera::calcThread, this, std::ref(world), std::ref(calcOne), pairOne.first, pairOne.second);
//	std::thread t2(&Camera::calcThread, this, std::ref(world), std::ref(calcTwo), pairTwo.first, pairTwo.second);
//	std::thread t3(&Camera::calcThread, this, std::ref(world), std::ref(calcThree), pairThree.first, pairThree.second);
//	std::thread t4(&Camera::calcThread, this, std::ref(world), std::ref(calcFour), pairFour.first, pairFour.second);
//
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//
//	printf("MERGED================================\n");
//	std::vector<Colour> mergedCalcs;
//	mergedCalcs.reserve(calcOne.size() + calcTwo.size() + calcThree.size() + calcFour.size());
//	mergedCalcs.insert(mergedCalcs.end(), calcOne.begin(), calcOne.end());
//	mergedCalcs.insert(mergedCalcs.end(), calcTwo.begin(), calcTwo.end());
//	mergedCalcs.insert(mergedCalcs.end(), calcThree.begin(), calcThree.end());
//	mergedCalcs.insert(mergedCalcs.end(), calcFour.begin(), calcFour.end());
//
//	std::vector<Colour>::iterator it = mergedCalcs.begin();
//
//	Canvas image(this->hSize, this->vSize, Colour());
//
//	for (int y = 0; y < this->vSize; y++)
//	{
//		for (int x = 0; x < this->hSize; x++)
//		{
//			//printf("(%f, %f, %f)\n", it->getRed(), it->getGreen(), it->getBlue());
//			if (it != mergedCalcs.end())
//			{
//				image.writePixel(x, y, *it);
//				it++;
//			}
//		}
//	}
//
//	return image;
//}
//
//void Camera::calcThread(World& world, std::vector<Colour>& calc, const int yBegin, const int yEnd) const
//{
//	for (int y = yBegin; y < yEnd; y++)
//	{
//		for (int x = 0; x < this->hSize; x++)
//		{
//			Ray r = this->rayForPixel(x, y);
//			calc.push_back(world.colourAt(r));
//			printf("%i %i\n", y, x);
//		}
//	}
//}
//
