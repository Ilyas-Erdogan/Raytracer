#pragma once
#include <vector>
#include <memory>

class Object
	: public std::enable_shared_from_this<Object>
{
public:
	// Constructors
	Object();
	Object(const Object& copyObject);
	~Object();

	// Overloaded Operators
	Object& operator=(const Object& other);
	bool operator==(const Object& rhs) const;
	bool operator!=(const Object& rhs) const;



	std::vector<class Intersection> getIntersections(const std::vector<Intersection>& intersections) const;
};

