#include "Matrix.h"
#include <iostream>
#include <stdexcept>

/**
* Initializes a Matrix object of given row and column size.\n
* Sets all values to zero.
* 
* @param rowLimit Number of rows in the matrix.
* @param columnLimit Number of columns in ther matrix.
*/
Matrix::Matrix(const int rowLimit, const int columnLimit)
    : rowSize { rowLimit }, columnSize{ columnLimit }
{
    for (int i = 0; i < rowSize; i++)
    {
        this->matrix.push_back(std::vector<double>());
        for (int j = 0; j < columnSize; j++)
        {
            this->matrix[i].push_back(0.0);
        }
    }
}

/**
* Intializes a Matrix object from given 2-dimensional vector.\n
* Sets matrix row and column count according to given 2-dimensional vector.
* 
* @param matrixSet Reference to matrix object represented as 2-dimensional vector.
*/
Matrix::Matrix(const std::vector<std::vector<double>>& matrixSet)
    : matrix { matrixSet }
{
    this->rowSize = matrix[0].size();
    this->columnSize = matrix.size();
}

Matrix::~Matrix()
{
}

/**
* Accesses value from non-const Matrix object.
* 
* @param rowIndex Row index to access in the matrix.
* @param colIndex Column index to access in the matrix.
* @throws out_of_range error when either rowIndex or colIndex are too large.
* 
* @return double reference of value found at coordinate in Matrix.
*/
double& Matrix::operator()(int rowIndex, int colIndex)
{
    try
    {
        if ((rowIndex >= 0 && rowIndex < this->rowSize) && (colIndex >= 0 && colIndex < this->columnSize))
        {
            return matrix[rowIndex][colIndex];
        }
        else
        {
            throw std::out_of_range("Index/Indices not in bound of matrix!");
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


/**
* Accesses value from const Matrix object.
*
* @param rowIndex Row index to access in the matrix.
* @param colIndex Column index to access in the matrix.
* @throws out_of_range Error when either rowIndex or colIndex are too large.
*
* @return double value found at coordinate in Matrix.
*/
double Matrix::operator()(int rowIndex, int colIndex) const
{
    try
    {
        if ((rowIndex >= 0 && rowIndex < this->rowSize) && (colIndex >= 0 && colIndex < this->columnSize))
        {
            return matrix[rowIndex][colIndex];
        }
        else
        {
            throw std::out_of_range("Index/Indices not in bound of matrix!");
        }
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Checks for equality between two Matrix objects.
* 
* @param rhs Right-hand side matrix of equality.
* 
* @return True if both matrices have exact same row & column size and all values are the exact same, otherwise false.
*/
bool Matrix::operator==(const Matrix& rhs) const
{
    if (this->columnSize != rhs.columnSize || this->rowSize != rhs.rowSize)
    {
        return false;
    }
    
    for (int colLeft = 0, colRight = 0; colLeft < this->columnSize, colRight < rhs.columnSize; colLeft++, colRight++)
    {
        if (this->matrix[colLeft] != rhs.matrix[colRight])
        {
            return false;
        }
    }

    return true;
}

/**
* Checks for inequality between two Matrix objects.
*
* @param rhs Right-hand side matrix of inequality.
*
* @return False if both matrices have exact same row, column size, or all values are the exact same, otherwise true.
*/
bool Matrix::operator!=(const Matrix& rhs) const
{
    return !(*this == rhs);
}

/**
* Caluclates Hadamard product of calling matrix object by right-hand side matrix object.
* 
* @param rhs Right-hand side reference of matrix object.
* @throws exception If calling matrix row size is not equal to right-hand size matrix column size.
* 
* @return Matrix object of resultant Hadamard product.
*/
Matrix Matrix::operator*=(const Matrix& rhs)
{
    try
    {
        if (this->columnSize == rhs.rowSize)
        {
            Matrix returnMatrix(rhs.rowSize, this->columnSize);
            double val = 0;
            for (int row = 0; row < rhs.rowSize; row++)
            {
                for (int col = 0; col < this->columnSize; col++)
                {
                    for (int i = 0; i < rhs.rowSize; i++)
                    {
                        val += (*this)(row, i) * rhs(i, col);
                    }
                    returnMatrix.matrix[row][col] = val;
                    val = 0;
                }
            }
            return returnMatrix;
        }
        else
        {
            throw std::exception("First Matrix must have the same number of columns as the second matrix has rows!");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

Matrix operator*(Matrix lhs, const Matrix& rhs)
{
    lhs *= rhs;
    
    return lhs;
}
