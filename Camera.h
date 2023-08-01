#pragma once
#include "ViewTransform.h"
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

	// Setters
	void setTransform(const Matrix& transformToSet);

	// Utility
	double getPixelSize() const;
	const Ray rayForPixel(const int pX, const int pY) const;
	Canvas render(World& world) const;
private:
	double hSize;
	double vSize;
	double fieldOfView;
	Matrix transform;

	double halfWidth;
	double halfHeight;
	double pixelSize;
};

