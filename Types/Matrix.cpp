#include "Matrix.h"

#include <iostream>
#include <stdexcept>
#include <tuple>


/**
* Initializes a Matrix object of given row and column size.\n
* Sets all values to zero.
* 
* @param rowLimit Number of rows in the matrix.
* @param columnLimit Number of columns in ther matrix.
*/
Matrix::Matrix()
    : rowSize{ 0 }, columnSize{ 0 }
{
}
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
    this->rowSize = matrix.size();
    this->columnSize = matrix[0].size();
}

Matrix::~Matrix()
{
}

Matrix& Matrix::operator=(const Matrix& other)
{
    // Self-assignment guard
    if (this == &other)
    {
        return *this;
    }

    this->matrix = other.matrix;
    this->rowSize = other.rowSize;
    this->columnSize = other.columnSize;
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
    
    for (int row = 0; row < this->rowSize; row++)
    {
        for (int column = 0; column < this->columnSize; column++)
        {
            if (std::abs((*this)(row, column) - rhs(row, column)) > EPSILON)
            {
                return false;
            }
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
* @throws exception If calling matrix column size is not equal to rhs matrix row size.
* 
* @return Modified calling (resultant Hadamard product).
*/
Matrix& Matrix::operator*=(const Matrix& rhs)
{
    try
    {
        if (this->columnSize == rhs.rowSize)
        {
            Matrix returnMatrix(this->rowSize, rhs.columnSize);
            double val = 0;
            for (int row = 0; row < this->rowSize; row++)
            {
                for (int col = 0; col < rhs.columnSize; col++)
                {
                    for (int i = 0; i < rhs.rowSize; i++)
                    {
                        val += ((*this)(row, i) * rhs(i, col));
                    }
                    returnMatrix.matrix[row][col] = val;
                    val = 0;
                }
            }
            *this = returnMatrix;
            return *this;
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

/**
* Caluclates Hadamard product of left-hand side matrix object by right-hand side matrix object.
*
* @param rhs Right-hand side of matrix object.
* @param lhs Left-hand side reference of matrix object.
* @throws exception If lhs matrix column size is not equal to rhs matrix column size.
*
* @return Modified lhs matrix (resultant Hadamard product).
*/
Matrix operator*(Matrix lhs, const Matrix& rhs)
{
    try
    {
        if (lhs.columnSize == rhs.rowSize)
        {
            lhs *= rhs;
            return lhs;
        }
        throw std::exception("First Matrix must have the same number of columns as the second matrix has rows!");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns a Tuple object after multilpication by a Matrix.
* Function only supports matrices with a column size of 4!
* 
* @param Tuple lhs Left-hand side Tuple object.
* @param Matrix rhs Right-hand side Matrix reference object.
* @throws exception If rhs matrix column size is not equal to 4.
* 
* @return Tuple object of resultant multiplication.
*/
Tuple operator*(Tuple lhs, const Matrix& rhs)
{
    try
    {
        if (rhs.columnSize == 4)
        {
            // Convert tuple to matrix
            Matrix tupleMatrix = rhs * Matrix({ {lhs.getX()}, {lhs.getY()}, {lhs.getZ()}, {lhs.getW()} });
            // Convert back to Tuple
            return Tuple(tupleMatrix(0,0), tupleMatrix(1,0), tupleMatrix(2,0), tupleMatrix(3,0));
        }
        throw std::exception("Matrix object row size must be equal to four!");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns a Tuple object after multilpication by a Matrix.
* Function only supports matrices with a column size of 4!
*
* @param Matrix lhs Right-hand side Matrix object.
* @param Tuple rhs Left-hand side Tuple reference object.
* @throws exception If lhs matrix column size is not equal to 4.
*
* @return Tuple object of resultant multiplication.
*/
Tuple operator*(Matrix lhs, const Tuple& rhs)
{
    Tuple tempTuple = rhs;
    return tempTuple * lhs;
}

bool operator<(const Matrix& l, const Matrix& r)
{
    return std::tie(l.rowSize, l.columnSize, l.matrix) < std::tie(r.rowSize, r.columnSize, r.matrix);
}

const std::vector<std::vector<double>>& Matrix::getMatrix() const
{
    return this->matrix;
}

/**
* Returns an identity matrix according to the size of the calling object's Matrix.
* 
* @throws exception If calling object's matrix is not a square.
* 
* @return Identity matrix.
*/
Matrix Matrix::getIdentityMatrix() const
{
    try
    {
        if (this->rowSize == this->columnSize)
        {
            Matrix returnMatrix(this->rowSize, this->columnSize);
            for (int row = 0; row < this->rowSize; row++)
            {
                for (int col = 0; col < this->columnSize; col++)
                {
                    if (row == col)
                    {
                        returnMatrix.matrix[row][col] = 1;
                        break;
                    }
                }
            }
            return returnMatrix;
        }
        throw std::exception("No identity matrix for a non-squre matrix!");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns the transposed matrix of calling object's matrix.
*/
Matrix Matrix::getTransposedMatrix() const
{
    Matrix transposedMatrix(this->rowSize, this->columnSize);
    for (int row = 0; row < this->rowSize; row++)
    {
        for (int col = 0; col < this->columnSize; col++)
        {
            transposedMatrix.matrix[col][row] = (*this)(row, col);
        }
    }
    return transposedMatrix;
}

/**
* Calcualtes the determinant of the calling matrix.
* 
* @throws exception If the calling matrix is not a square matrix.
* 
* @return Value of the determinant.
*/
double Matrix::getDeterminant() const
{
    try
    {
        if (this->rowSize == 2 && this->columnSize == 2)
        {
            
            return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));
        }
        else if (this->rowSize == this->columnSize)
        {
            double det = 0;
            for (int column = 0; column < this->rowSize; column++)
            {
                det += (*this)(0, column) * this->getCofactor(0, column);
            }
            return det;
        }
        else
        {
            throw std::exception("Cannot find determinant of a non-square matrix!");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns a Matrix object containing the requested submatrix.
* 
* @param int row Row index to be removed.
* @param int column Column index to be removed.
* @throws out_of_range If the row and/or column values are not within the appropriate ranges.
* 
* @return Submatrix of the calling object.
*/
Matrix Matrix::getSubmatrix(int row, int column) const
{
    try
    {
        if ((row >= 0 && row < this->rowSize) && (column >= 0 && column < this->columnSize))
        {
            Matrix returnMatrix = *this;
            // Delete the specified row
            returnMatrix.matrix.erase(returnMatrix.matrix.begin() + row);
            // Decrease row size prior to iteration
            returnMatrix.rowSize--;
            for (int i = 0; i < returnMatrix.rowSize; i++)
            {
                returnMatrix.matrix[i].erase(returnMatrix.matrix[i].begin() + column);
            }
            returnMatrix.columnSize--;
            return returnMatrix;
        }
        throw std::out_of_range("Row and/or column index to remove not within valid range!");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns the minor (determinant of the submatrix) of the calling object's matrix.
* 
* @param int row Row to be omitted when finding the submatrix.
* @param int column Column to be omitted when finding the submatrix.
* @throws out_of_range If the row and/or column values are not within the appropriate ranges.
* 
* @return Value of the minor of the matrix.
*/
double Matrix::getMinor(int row, int column) const
{
    try
    {
        if ((row >= 0 && row < this->rowSize) && (column >= 0 && column < this->columnSize))
        {
            return this->getSubmatrix(row, column).getDeterminant();
        }
        throw std::out_of_range("Invalid row and/or column index provided!");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Returns the minor of the calling object's matrix with the appropriate sign (+/-).
* 
* @param int row Row to be removed when calcualting the submatrix.
* @param int column Column to be removed when calculating the submatrix.
* @throws out_of_range If the row and/or column values are not within the appropriate ranges.
* 
* @return 
*/
double Matrix::getCofactor(int row, int column) const
{
    try
    {
        if ((row >= 0 && row < this->rowSize) && (column >= 0 && column < this->columnSize))
        {
            // Determine appropraite sign
            return (((row + column) % 2 == 0) ? (this->getMinor(row, column)) : (-1 * this->getMinor(row, column)));
        }
        throw std::out_of_range("Invalid row and/or column index provided!");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

/**
* Determines whether or not the calling object's matrix is invertible.
* A matrix is deemed invertible if it's determinant is not equal to 0.
* 
* @return True if the matrix has non-zero determinant, otehrwise false.
*/
bool Matrix::isInvertible() const
{
    return !(this->getDeterminant() == 0);
}


/**
* Returns a matrix containing the inverse matrix of the calling object's matrix.
* 
* @throws exception If the matrix is not invertible.
* 
* @return Inverse matrix of the calling object.
*/
Matrix Matrix::getInverse() const
{
    try
    {
        if (this->isInvertible())
        {
            Matrix invertedMatrix(this->rowSize, this->columnSize);
            double c = 0;
            for (int row = 0; row < this->rowSize; row++)
            {
                for (int column = 0; column < this->columnSize; column++)
                {
                    c = this->getCofactor(row, column);
                    invertedMatrix.matrix[column][row] = (c / this->getDeterminant());
                }
            }
            return invertedMatrix;
        }
        throw std::exception("Matrix is not invertible!");
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void Matrix::setMatrix(const Matrix& matrix)
{
    this->matrix = matrix.getMatrix();
}
