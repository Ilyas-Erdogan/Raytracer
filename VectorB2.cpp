#include "VectorB2.h"

Vector& VectorB2::operator[](const int index)
{
    return this->vertices[index - 1];
}

const Vector& VectorB2::operator[](const int index) const
{
    return this->vertices[index - 1];
}

const size_t VectorB2::size() const
{
    return this->vertices.size();
}

void VectorB2::push_back(const Vector& vec)
{
    this->vertices.push_back(vec);
}
