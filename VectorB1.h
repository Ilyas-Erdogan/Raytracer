#pragma once
#include <vector>>
#include "Types/Point.h"
class VectorB1
{
public:
	std::vector<Point> vertices;
	Point& operator[](const int index);
	const Point& operator[](const int index) const;
	const size_t size() const;
	void push_back(const Point& point);
};

