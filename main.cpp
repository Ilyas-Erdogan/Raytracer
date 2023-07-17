#include <iostream>
#include "Vector.h"
#include "Point.h"
#include "Canvas.h"
#include "Colour.h"
#include "Matrix.h"


struct Projectile
{
	Point Position;
	Vector Velocity;
	Projectile(Point p, Vector v) : Position{ p }, Velocity{ v } {};
};

struct Environment
{
	Vector Gravity;
	Vector Wind;
	Environment(Vector g, Vector w) : Gravity{ g }, Wind{ w } {};
};

Projectile tick(Environment env, Projectile proj)
{
	Vector position = proj.Position + proj.Velocity;
	Vector velocity = proj.Velocity + env.Gravity + env.Wind;
	return Projectile(position, velocity);
}

int main()
{
	//Point Start(0, 1, 0);
	//Vector Velocity(1, 1.8, 0);
	//Velocity.normalizeVector();
	//Velocity *= 11.25;
	//Projectile p(Start, Velocity);

	//Vector Gravity(0, -0.1, 0);
	//Vector Wind(-0.01, 0, 0);
	//Environment e(Gravity, Wind);

	//Canvas c(900, 550, Colour());

	//int tickCount = 0;

	//while (p.Position.getY() >= 0)
	//{
	//	p = tick(e, p);
	//	c.writePixel(static_cast<int>(p.Position.getX()), c.getCanvasHeight() - static_cast<int>(p.Position.getY()), Colour(1, 1, 1));
	//	tickCount++;
	//	std::cout << p.Position.getX() << " " << p.Position.getY() << " " << p.Position.getZ() << '\n';
	//}

	//c.convertToPPM("projectile");
	//std::cout << tickCount << '\n';
	return 0;
}