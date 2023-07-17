#pragma once
#include <vector>

class Matrix
{
public:
	// Constructors
	Matrix(const int rowLimit, const int columnLimit);
	Matrix(const std::vector < std::vector<double>>& matrixSet);
	~Matrix();

	// Overloaded operators
	double& operator()(int rowIndex, int colIndex);
	double operator()(int rowIndex, int colIndex) const;

	bool operator==(const Matrix& rhs) const;
	bool operator!=(const Matrix& rhs) const;

	Matrix operator*=(const Matrix& rhs);
	friend Matrix operator*(Matrix lhs, const Matrix& rhs);

	//class Tuple operator*=(const Matrix& rhs);
	friend class Tuple operator*(class Tuple& lhs, const Matrix& rhs);
	friend class Tuple operator*(Matrix& lhs, const class Tuple& rhs);

private:
	// Limits
	int rowSize;
	int columnSize;
	
	// 2-Dimensional vector matrix
	std::vector<std::vector<double>> matrix;
};

