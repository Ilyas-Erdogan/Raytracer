#include <iostream>
#include "Canvas.h"
#include "Colour.h"

int main()
{
	Canvas c(5, 3);
	c.writePixel(0, 0, Colour(0.573, 0, 0));
	c.writePixel(2, 1, Colour(0, 0.53, 0));
	c.writePixel(4, 2, Colour(0, 0, 0.912));
	c.convertToPPM("my_image");
}