#include "Container.h"

Tuple& Container::operator[](int index)
{
    return this->container[index-1];
}

const Tuple& Container::operator[](int index) const
{
    return this->container[index - 1];
}

void Container::push_back(const Tuple& item)
{
    this->container.push_back(item);
}

int Container::size() const
{
    return this->container.size();
}
