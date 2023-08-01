#include "Camera.h"
#include <cmath>
#include <chrono>

Camera::Camera(const double horizontalSize, const double verticalSize, const double fieldOfViewVal)
	: transform{ Matrix(4, 4).getIdentityMatrix()}, hSize{horizontalSize}, vSize{verticalSize}, fieldOfView{fieldOfViewVal}
{
	double halfView = std::tan(this->fieldOfView / 2);
	double aspect = this->hSize / this->vSize;
	if (aspect >= 1.0)
	{
		this->halfWidth = halfView;
		this->halfHeight = halfView / aspect;
	}
	else
	{
		this->halfWidth = halfView * aspect;
		this->halfHeight = halfView;
	}

	this->pixelSize = (halfWidth * 2) / this->hSize;
}

Camera::~Camera()
{
}

double Camera::getHorizontalSize() const
{
	return this->hSize;
}

double Camera::getVerticalSize() const
{
	return this->vSize;
}

double Camera::getFieldOfView() const
{
	return this->fieldOfView;
}

const Matrix& Camera::getTransform() const
{
	return this->transform;
}

void Camera::setTransform(const Matrix& transformToSet)
{
	this->transform = transformToSet;
}

double Camera::getPixelSize() const
{
	return this->pixelSize;
}

const Ray Camera::rayForPixel(const int pX, const int pY) const
{
	// The offset from teh edge of the canvas to the pixel's center
	double xOffset = (pX + 0.5) * this->pixelSize;
	double yOffset = (pY + 0.5) * this->pixelSize;

	// The untransformed coordinates of the pixel in the world space
	double worldX = this->halfWidth - xOffset;
	double worldY = this->halfHeight - yOffset;

	// Using camera matrix, transform the canvas point and origin, and compute ray's direction vector
	Point pixel = this->transform.getInverse() * Point(worldX, worldY, -1);
	Point origin = this->transform.getInverse() * Point(0, 0, 0);
	Vector direction = (pixel - origin).normalizeVector();

	return Ray(origin, direction);

}

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

	return image;
}

