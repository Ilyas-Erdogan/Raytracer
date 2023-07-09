#pragma once
#include <vector>
#include <string>

class Canvas
{
public:
	// Constructors
	Canvas(int width, int height);
	~Canvas();
private:
	std::vector<std::vector<class Colour>> pixels;
public:
	// Getters
	std::vector<std::vector<class Colour>> getCanvas();
	int getCanvasWidth() const;
	int getCanvasHeight() const;

	// Utility
	bool writePixel(const int x, const int y, const Colour colour);
	Colour getPixel(const int x, const int y);
	void convertToPPM(const std::string fileName);
};

