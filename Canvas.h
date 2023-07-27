#pragma once
#include <vector>
#include <string>
#include "Types/Colour.h"

class Canvas
{
public:
	// Constructors
	Canvas(int width, int height, const Colour& canvasColour);
	~Canvas();
private:
	std::vector<std::vector<class Colour>> pixels;
public:
	// Getters
	std::vector<std::vector<class Colour>> getCanvas();
	int getCanvasWidth() const;
	int getCanvasHeight() const;

	// Utility
	bool writePixel(const int x, const int y, const class Colour& colour);
	Colour getPixel(const int x, const int y);
	void convertToPPM(const std::string fileName);
};

