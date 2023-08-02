#pragma once
#include <vector>
#include "Tuple.h"

class Matrix
{
public:
	// Constructors
	Matrix();
	Matrix(const int rowLimit, const int columnLimit);
	Matrix(const std::vector < std::vector<double>>& matrixSet);
	~Matrix();

	// Overloaded operators
	Matrix& operator=(const Matrix& other);

	double& operator()(int rowIndex, int colIndex);
	double operator()(int rowIndex, int colIndex) const;

	bool operator==(const Matrix& rhs) const;
	bool operator!=(const Matrix& rhs) const;

	Matrix& operator*=(const Matrix& rhs);
	friend Matrix operator*(Matrix lhs, const Matrix& rhs);

	friend class Tuple operator*(class Tuple lhs, const Matrix& rhs);
	friend class Tuple operator*(Matrix lhs, const class Tuple& rhs);

	friend bool operator<(const Matrix& l, const Matrix& r);
	
	// Utilities
	const std::vector<std::vector<double>>& getMatrix() const;
	Matrix getIdentityMatrix() const;
	Matrix getTransposedMatrix() const;
	double getDeterminant() const;
	Matrix getSubmatrix(int row, int column) const;
	double getMinor(int row, int column) const;
	double getCofactor(int row, int column) const;
	bool isInvertible() const;
	Matrix getInverse() const;

	// Setters
	void setMatrix(const Matrix& matrix);
protected:
	// Constants
	const double EPSILON{ 0.00001 };

	// Limits
	int rowSize;
	int columnSize;
	
	// 2-Dimensional vector matrix
	std::vector<std::vector<double>> matrix;
};

