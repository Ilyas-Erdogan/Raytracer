#include <iostream>
#include "Vector.h"
#include "Point.h"
#include "Canvas.h"
#include "Colour.h"
#include "Matrix.h"
#include "Translation.h"
#include "Scale.h"
#include "RotationX.h"
#include "RotationY.h"
#include "RotationZ.h"
#include "Shearing.h"


int main()
{
	Canvas c(100, 100, Colour());
	const double pi = 3.1415926535897932385;

	Point origin(50, 0, 50);
	Point twelve(0, 0, 1);

	for (int i = 0; i < 12; i++)
	{
		Point toDraw = twelve * RotationY(i * pi / 6);
		toDraw *= 3.0/8;
		c.writePixel(origin.getX() + static_cast<int>(toDraw.getX() * c.getCanvasWidth()), origin.getZ() + static_cast<int>(toDraw.getZ() * c.getCanvasHeight()), Colour(1, 1, 1));
	}

	c.convertToPPM("clock");
	
	return 0;
}