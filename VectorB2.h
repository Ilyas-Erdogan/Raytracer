#pragma once
#include <vector>
#include "Types/Vector.h"
class VectorB2
{
public:
	std::vector<Vector> vertices;
	Vector& operator[](const int index);
	const Vector& operator[](const int index) const;
	const size_t size() const;
	void push_back(const Vector& vec);
};

