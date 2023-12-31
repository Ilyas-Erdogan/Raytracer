#pragma once
#include "Transformations/ViewTransform.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"


class Camera
{
public:
	// Constructors
	Camera(const double horizontalSize, const double verticalSize, const double fieldOfViewVal);
	~Camera();

	// Getters
	double getHorizontalSize() const;
	double getVerticalSize() const;
	double getFieldOfView() const;
	const Matrix& getTransform() const;
	const Matrix& getInverseTransform() const;

	// Setters
	void setTransform(const Matrix& transformToSet);

	// Utility
	double getPixelSize() const;
	const Ray rayForPixel(const int pX, const int pY) const;
	// Default Render
	Canvas render(World& world) const;
	// Multithread expirementation
	//const Canvas render(World& world) const;
	//void calcThread(World& world, std::vector<Colour>& calc, const int yBegin, const int yEnd) const;

private:
	double hSize;
	double vSize;
	double fieldOfView;
	Matrix transform;

	double halfWidth;
	double halfHeight;
	double pixelSize;
	Matrix inverseTransform;
};

