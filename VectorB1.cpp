#include "VectorB1.h"

Point& VectorB1::operator[](const int index)
{
    return this->vertices[index - 1];
}

const Point& VectorB1::operator[](const int index) const
{
    return this->vertices[index - 1];
}

const size_t VectorB1::size() const
{
    return this->vertices.size();
}

void VectorB1::push_back(const Point& point)
{
    this->vertices.push_back(point);
}
