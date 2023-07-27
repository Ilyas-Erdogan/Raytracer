#pragma once

class Tuple
{
public:
	// Constructor
	Tuple(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double w = 0.0);
	~Tuple();
	
	// Overloaded operators
	Tuple& operator=(const Tuple& other);

	bool operator==(const Tuple& rhs) const;
	bool operator!=(const Tuple& rhs) const;

	Tuple& operator+=(const Tuple& rhs);
	friend Tuple operator+(Tuple lhs, const Tuple& rhs);

	Tuple& operator-=(const Tuple& rhs);
	friend Tuple operator-(Tuple lhs, const Tuple& rhs);
	Tuple operator-() const;

	Tuple& operator*=(const double value);
	friend Tuple operator*(Tuple lhs, const double value);
	friend Tuple operator*(const double value, const Tuple& rhs);

	Tuple& operator/=(const double value);
	friend Tuple operator/(Tuple lhs, const double value);
	friend Tuple operator/(const double value, const Tuple& rhs);

protected:
	// Coordinates
	double x;
	double y;
	double z;
	double w;

	// Comparison value
	const double EPSILON{ 0.00001 };
public:
	// Member getters
	double getX() const;
	double getY() const;
	double getZ() const;
	double getW() const;
	
	// Checkers
	bool isPoint() const;
	bool isVector() const;

	// Utilities
	double getMagnitude() const;
	Tuple normalizeVector() const;
	double dotProduct(const Tuple& secondTerm) const;
	Tuple crossProduct(const Tuple& secondTerm) const;
};
