// sayyid muhammad baqir rizavi
// bcsf19m053
// morning
#include "Matrix.h"
using namespace std;


Matrix::Matrix() : Matrix(5, 5)
{}
Matrix::Matrix(const int r, const int c)
{
	rows = r;
	cols = c;
	
	// declare matrix on heap
	ptr = new int* [r];
	for (int i = 0; i < r; i++)
	{
		ptr[i] = new int[c];
	} 

	// putting 0s in matrix
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			ptr[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix& m)
{
	rows = m.rows;
	cols = m.cols;

	// declare matrix on heap
	ptr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		ptr[i] = new int[cols];
	}

	// copy matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ptr[i][j] = m.ptr[i][j];
		}
	}
}
Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] ptr[i];
		ptr[i] = nullptr;
	}
	delete[] ptr;
	ptr = nullptr;
}
int Matrix::getRows() const
{
	return rows;
}
int Matrix::getCols() const
{
	return cols;
}
const Matrix& Matrix::operator = (const Matrix& m)
{
	// self asssignment check
	if (this == &m)
	{
		return *this;
	}

	// destroying previous memory
	for (int i = 0; i < rows; i++)
	{
		delete[] ptr[i];
		ptr[i] = nullptr;
	}
	delete[] ptr;
	ptr = nullptr;

	// other copy member variables
	rows = m.rows;
	cols = m.cols;
	
	// reallocate
	ptr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		ptr[i] = new int[cols];
	}

	// copy matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ptr[i][j] = m.ptr[i][j];
		}
	}

	return *this;
}
int& Matrix::operator () (int i, int j)
{
	return ptr[i][j];
}
Matrix Matrix::operator + (const Matrix& m) const
{
	// check if matrix can be added
	if (m.cols != cols || m.rows != rows)
	{
		Matrix new1(1, 1);
		new1(0, 0) = -888;
		return new1;
	}

	// create new 2d matrix
	Matrix new1(rows, cols);
	new1.cols = cols;
	new1.rows = rows;

	// add matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new1.ptr[i][j] = ptr[i][j] + m.ptr[i][j];
		}
	}
	return new1;
}
Matrix Matrix::operator * (const Matrix& m) const
{
	// check if matrix can be multiplied
	if (cols != m.rows)
	{
		Matrix new1(1, 1);
		new1(0, 0) = -999;
		return new1;
	}

	// create new 2d matrix
	Matrix new1(rows, m.cols);	// the result of matrix multipications
	new1.cols = m.cols;				// inherit the rows of 1st and columns
	new1.rows = rows;				// of 2nd matrix

	// multiply matrix
	for (int i = 0; i < new1.rows; i++)
	{
		for (int j = 0; j < new1.cols; j++)
		{
			for (int k = 0; k < cols; k++)					// this loop will dot product the row vector  
			{												// "i" from the first matrix and column vector 
				new1.ptr[i][j] += ptr[i][k] * m.ptr[k][j];	// "j" from the second and store it in [i][j]
			}												// position of resultant matrix	
		} 
	}

	return new1;
}
void Matrix::operator *= (int n)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ptr[i][j] *= n;
		}
	}
}
void Matrix::operator ! () 
{
	Matrix new1(cols, rows); // new matrix with swap rows and cols

	// copying in a revesed rows/cols manner 
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new1.ptr[j][i] = ptr[i][j];
		}
	}
	
	*this = new1; // assign it to orignal matrix
}
Matrix Matrix::minor(int i, int j) const 
{
	Matrix min(rows - 1, cols - 1);
	for (int r = 0, ro = 0; r < min.rows; r++, ro++)
	{
		if (i == ro)
		{
			ro++;
		}
		for (int c = 0, co = 0; c < min.cols; c++, co++)
		{
			if (j == co)
			{
				co++;
			}
			min.ptr[r][c] = ptr[ro][co];	
		}
	}
	return min;
}
int Matrix::determinant() const
{
	if (rows == 1) 
	{ 
		return ptr[0][0]; 
	}
	int det = 0;
	for (int i = 0; i < cols; i++)
	{
		det += (pow(-1, 0 + i) * ptr[0][i] * this->minor(0, i).determinant());
	}
	return det;
}