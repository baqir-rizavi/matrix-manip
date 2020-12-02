// sayyid muhammad baqir rizavi
// bcsf19m053
// morning
#ifndef Matrix_H
#define Matrix_H
#include <iostream>
using namespace std;

class Matrix
{
private:
	int** ptr;	// point to matrix on heap
	int rows;
	int cols;
	Matrix minor(int, int) const;
public:
	Matrix();
	Matrix(const int, const int);
	Matrix(const Matrix&);
	~Matrix();
	//-------------------------> getters
	int getRows() const;
	int getCols() const;
	//-------------------------> operators
	const Matrix& operator = (const Matrix&);
	int& operator () (int, int);
	Matrix operator + (const Matrix&) const;
	Matrix operator * (const Matrix&) const;
	void operator *= (int);
	void operator ! ();
	//-------------------------> features
	int determinant() const;
	//-------------------------> friends
	friend ostream& operator << (ostream&, const Matrix&);
	friend istream& operator >> (istream&, Matrix&);
};
#endif // !Matrix_H

