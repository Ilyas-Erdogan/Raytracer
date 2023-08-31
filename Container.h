#pragma once
#include "Types/Tuple.h"
#include <vector>

class Container
{
public:
	Tuple& operator[] (int index);
	const Tuple& operator[](int index) const;
	void push_back(const Tuple& item);
	int size() const;
public:
	std::vector<Tuple> container;
};

