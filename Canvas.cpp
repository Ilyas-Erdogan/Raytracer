#include "Canvas.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Colour.h"

Canvas::Canvas(int width, int height, Colour canvasColour)
{
	this->pixels = pixels;
	this->pixels.resize(height, std::vector<Colour>());
	// Populate canvas with provided colour (default BLACK)
	for (auto& i : this->pixels)
	{
		i.resize(width, canvasColour);
	}
}

Canvas::~Canvas()
{
}

/**
* Returns current canvas as a 2-dimensional vector.
* 
* @return Current canvas.
*/
std::vector<std::vector<class Colour>> Canvas::getCanvas()
{
	return this->pixels;
}

/**
* Returns canvas width of calling object.
*
* @return Width of calling canvas object.
*/
int Canvas::getCanvasWidth() const
{
	return pixels[0].size();
}

/**
* Returns canvas height of calling object.
*
* @return Height of calling canvas object.
*/
int Canvas::getCanvasHeight() const
{
	return pixels.size();
}

/**
* Writes a RGB colour to the canvas.
* Verifies passed-in coordinates.
* 
* @param x Integer value of canvas x-coordinate. Range: [0, width - 1]
* @param y Integer value of canvas y-coordinate. Range: [0, height - 1]
* @param colour Colour object to set pixel.
* 
* @return True for succesful write, otherwise false.
*/
bool Canvas::writePixel(const int x, const int y, const Colour colour)
{
	if (x <= this->getCanvasWidth() - 1 && y <= this->getCanvasHeight() - 1)
	{
		this->pixels[y][x] = colour;
		return true;
	}

	std::cerr << "Could not write pixel to canvas. Double check parameters.\n";
	return false;
}

/**
* Returns a RGB colour from given point on canvas.
* Verifies passed-in coordinates.
*
* @param x Integer value of canvas x-coordinate. Range: [0, width - 1]
* @param y Integer value of canvas y-coordinate. Range: [0, height - 1]
*
* @return Colour object at point, otherwise invalid colour.
*/
Colour Canvas::getPixel(const int x, const int y)
{
	if (x <= this->getCanvasWidth() - 1 && y <= this->getCanvasHeight())
	{
		return this->pixels[x][y];
	}

	std::cerr << "Could not write pixel to canvas. Double check parameters.\n";
	return Colour(-1, -1, -1);
}

/**
* Write canvas RGB values to text file with PPM (Portable Pixel Map) headings.
* 
* @param fileName String to name file as.
*
* @return Void.
*/
void Canvas::convertToPPM(const std::string fileName)
{
	std::ofstream file(fileName + ".ppm", std::ofstream::trunc);
	if (!file)
	{
		std::cerr << "Cannot open file: " << fileName << '\n';
		std::exit(-1);
	}
	file << "P3\n";
	file << this->getCanvasWidth() << " " << this->getCanvasHeight() << "\n";
	file << "255\n";
	
	int count = 0;
	std::string tempRed;
	std::string tempGreen;
	std::string tempBlue;
	// Populate pixel map
	// Design Note: Limit max characters per line to 70
	for (auto row : this->pixels)
	{
		for (auto col : row)
		{
			tempRed = std::to_string(std::clamp(static_cast<int>(col.getRed() * 255), 0, 255));
			tempGreen = std::to_string(std::clamp(static_cast<int>(col.getGreen() * 255), 0, 255));
			tempBlue = std::to_string(std::clamp(static_cast<int>(col.getBlue() * 255), 0, 255));
			
			count += tempRed.length();
			if (count >= 69)
			{
				tempRed += '\n';
				count = 0;
			}
			else
			{
				tempRed += ' ';
				count++;
			}
			count += tempBlue.length();
			if (count >= 69)
			{
				tempGreen += '\n';
				count = 0;
			}
			else
			{
				tempGreen += ' ';
				count++;
			}
			count += tempGreen.length();
			if (count >= 69)
			{
				tempBlue += '\n';
				count = 0;
			}
			else
			{
				tempBlue += ' ';
				count++;
			}

			file << tempRed << tempGreen << tempBlue;
		}
		if (tempBlue[tempBlue.length() - 1] != '\n')
		{
			file << '\n';
		}
		count = 0;
	}
	file<< '\n';
	
	file.close();
}
