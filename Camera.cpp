#include "Camera.h"
#include <cmath>
#include <chrono>
#include <utility>

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
	for (int y = 0; y < this->vSize; y++)
	{
		begin = std::chrono::high_resolution_clock::now();
		for (int x = 0; x < this->hSize; x++)
		{
			Ray r = this->rayForPixel(x, y);
			Colour colour = world.colourAt(r);
			image.writePixel(x, y, colour);
			//printf("Time measured: %.3f seconds.\n", sum.count() * 1e-9);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		sum += elapsed;
		printf("Time measured: %.3f seconds.\n", sum.count() * 1e-9);
	}
	printf("Time measured: %.3f seconds.\n", sum.count() * 1e-9);
	printf("FINI");

	return image;
}

