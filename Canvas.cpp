#include "Canvas.h"

#include <iostream>
#include <fstream>
#include "Colour.h"

Canvas::Canvas(int width, int height)
{
	this->pixels = pixels;
	this->pixels.resize(height, std::vector<Colour>());
	for (auto& i : this->pixels)
	{
		i.resize(width, Colour());
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
	std::ofstream file(fileName + ".ppm");
	if (!file)
	{
		std::cerr << "Cannot open file: " << fileName << '\n';
		std::exit(-1);
	}
	file << "P3\n";
	file << this->getCanvasWidth() << " " << this->getCanvasHeight() << "\n";
	file << "255\n";
	
	for (auto row : this->pixels)
	{
		for (auto col : row)
		{
			int tempRed = col.getRed() * 255;
			int tempGreen = col.getGreen() * 255;
			int tempBlue = col.getBlue() * 255;

			if (tempRed < 0)
			{
				tempRed = 0;
			}
			else if (tempRed > 255)
			{
				tempRed = 255;
			}
			if (tempGreen < 0)
			{
				tempGreen = 0;
			}
			else if (tempGreen > 255)
			{
				tempGreen = 255;
			}
			if (tempBlue < 0)
			{
				tempBlue = 0;
			}
			else if (tempBlue > 255)
			{
				tempBlue = 255;
			}
			file << tempRed << " " << tempGreen << " " << tempBlue << " ";
		}
	}

	file.close();
}
