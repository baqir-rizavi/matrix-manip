// sayyid muhammad baqir rizavi
// bcsf19m053
// morning
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Matrix.h"
using namespace std;

ostream& operator << (ostream&, const Matrix&);
istream& operator >> (istream&, Matrix&);
void openFile(ifstream&);
Matrix* allocateMatrixArray(int);
void readMatricesFromFile(int, Matrix*, ifstream&);
void mainMenu(int, Matrix*);
void validateOption(int&, int, int);
void displayMatrix(int , Matrix*);
void displayMatrices(int, Matrix*);
void modifyElement(int, Matrix*);
void madifyMatrix(int, Matrix*);
void transposeMatrix(int, Matrix*);
void addMatrices(int, Matrix*);
void multiplyMatrices(int, Matrix*);
void mulIntMatrix(int, Matrix*);
void findDeterminant(int, Matrix*);

//======================================================
int main()//----------------> " MAIN "
{
	ifstream fin;
	openFile(fin);
	int size; 
	fin >> size;
	Matrix* ptr;
	ptr = allocateMatrixArray(size);
	readMatricesFromFile(size, ptr, fin);
	fin.close();   // closed after reading
	//---------------------------------------
	mainMenu(size, ptr); // all path recursive except "Quit" option 
	//---------------------------------------
	delete[] ptr;
	ptr = nullptr;
	return 0;
}
//======================================================



void mainMenu(int size, Matrix* ptr)
{
	int option = 0;
	cout << "\n\n================================================\n"
		<< "MENU:                                           |\n"		
		<< "1. Display a matrix                             |\n"
		<< "2. Display ALL matrices                         |\n"
		<< "3. Modify an element in a matrix                |\n"
		<< "4. Modify a whole matrix                        |\n"
		<< "5. Take transpose of a matrix                   |\n"
		<< "6. Add two matrices                             |\n"
		<< "7. Multiply two matrices                        |\n"
		<< "8. Multiply a matrix with an integer            |\n"
		<< "9. calculate determinant                        |\n"
		<< "0. quit                                         |\n"
		<< "================================================\n"
		<< "Enter your choice :	";
	cin >> option;
	validateOption(option, 0, 9);
	switch (option)
	{
	case 1:
		displayMatrix(size, ptr);
	case 2:
		displayMatrices(size, ptr);
	case 3:
		modifyElement(size, ptr);
	case 4:
		madifyMatrix(size, ptr);
	case 5:
		transposeMatrix(size, ptr);
	case 6:
		addMatrices(size, ptr);
	case 7:
		multiplyMatrices(size, ptr);
	case 8:
		mulIntMatrix(size, ptr);
	case 9:
		findDeterminant(size, ptr);
	case 0:
		exit(0);
	};
}

void findDeterminant(int size, Matrix* ptr) // determinant
{
	int opt = -1;
	cout << "\nEnter which matrix's determinant you want: ";
	cin >> opt;
	validateOption(opt, 0, size - 1);
	if (ptr[opt].getRows() != ptr[opt].getCols())
	{
		cout << "\ndeterminant only possible on square matrix\n";
		mainMenu(size, ptr);
	}
	cout << ptr[opt].determinant();
	mainMenu(size, ptr);
}


void displayMatrix(int size, Matrix* ptr) // display single matrix
{
	int opt = -1;
	cout << "\nEnter which matrix you want to display: ";
	cin >> opt;
	validateOption(opt, 0, size - 1);
	cout << ptr[opt];
	mainMenu(size, ptr);
}



void displayMatrices(int size, Matrix* ptr) // display ALL MATRICES				
{
	cout << "\n";
	for (int i = 0; i < size; i++)
	{
		cout << ptr[i] << "\n\n";
	}
	mainMenu(size, ptr);
}



void modifyElement(int size, Matrix* ptr) // modify element 
{
	int opt = -1;
	cout << "\nEnter which matrix you want to modify: ";
	cin >> opt;
	validateOption(opt, 0, size - 1);
	int r = -1;
	cout << "Enter row: ";
	cin >> r;
	validateOption(r, 0, ptr[opt].getRows() - 1);
	int c = -1;
	cout << "Enter column: ";
	cin >> c;
	validateOption(c, 0, ptr[opt].getCols() - 1);
	cout << "Enter \"value\" to modify matrix # " << opt << " element(" << r << ',' << c << "): ";
	cin >> ptr[opt](r, c);
	cout << "Operation successful!\n";
	mainMenu(size, ptr);
}



void madifyMatrix(int size, Matrix* ptr) // modify matrix 
{
	int opt = -1;
	cout << "\nEnter which matrix you want to modify: ";
	cin >> opt;
	validateOption(opt, 0, size - 1);
	cout << "First enter rows then columns of matrix and then the matrix\n";
	cin >> ptr[opt];
	mainMenu(size, ptr);
}



void transposeMatrix(int size, Matrix* ptr) // transpose 
{
	int opt = -1;
	cout << "\nEnter which matrix you want to transpose: ";
	cin >> opt;
	validateOption(opt, 0, size - 1);
	cout << "before transpose:\n" << ptr[opt];
	!ptr[opt];
	cout << "after transpose:\n" << ptr[opt];
	mainMenu(size, ptr);
}




void addMatrices(int size, Matrix* ptr) // matrices addition
{
	int op1 = -1;
	cout << "\nEnter the matrix # of 1st matrix (left operand): ";
	cin >> op1;
	validateOption(op1, 0, size - 1);
	int op2 = -1;
	cout << "\nEnter the matrix # of 2nd matrix (right operand): ";
	cin >> op2;
	validateOption(op2, 0, size - 1);
	int op3 = -1;
	cout << "\nEnter matrix # of the destination matrix (resulting matrix): ";
	cin >> op3;
	validateOption(op3, 0, size - 1);
	ptr[op3] = ptr[op1] + ptr[op2];
	cout << "\nOperation successful!\n";
	mainMenu(size, ptr);
}




void multiplyMatrices(int size, Matrix* ptr) // matrix multiplication
{
	int op1 = -1;
	cout << "\nEnter the matrix # of 1st matrix (left operand): ";
	cin >> op1;
	validateOption(op1, 0, size - 1);
	int op2 = -1;
	cout << "\nEnter the matrix # of 2nd matrix (right operand): ";
	cin >> op2;
	validateOption(op2, 0, size - 1);
	int op3 = -1;
	cout << "\nEnter matrix # of the destination matrix (resulting matrix): ";
	cin >> op3;
	validateOption(op3, 0, size - 1);
	ptr[op3] = ptr[op1] * ptr[op2];
	cout << "\nOperation successful!\n";
	mainMenu(size, ptr);
}



void mulIntMatrix(int size, Matrix* ptr) // integer multiplication
{
	int op1 = -1;
	cout << "\nEnter the matrix # : ";
	cin >> op1;
	validateOption(op1, 0, size - 1);
	int num = 0;
	cout << "\nEnter the matrix # : ";
	cin >> num;
	cout << "before integer multiplication:\n" << ptr[op1];
	ptr[op1] *= num;
	cout << "after integer multiplication:\n" << ptr[op1];
	mainMenu(size, ptr);
}




void validateOption(int& o, int a, int b)
{
	while (o<a || o>b)
	{
		cout << "\nwrong option enter again: ";
		cin >> o;
	}
}




void readMatricesFromFile(int size, Matrix* ptr, ifstream& fin)
{
	for (int i = 0; i < size; i++)
	{
		fin >> ptr[i];
	}
}




Matrix* allocateMatrixArray(int size)
{ 
	Matrix* ptr = new Matrix[size];
	return ptr;
}



void openFile(ifstream& fin)
{
	fin;
	string name;
	cout << "Enter input fiie name: ";
	cin >> name;
	fin.open(name);
	if (!fin)						// test if file opened
	{
		cout << "\nError: file not opened\n";
		exit(0);
	}
}




istream& operator >> (istream& in, Matrix& m)
{
	// destroying previous memory
	for (int i = 0; i < m.rows; i++)
	{
		delete[] m.ptr[i];
		m.ptr[i] = nullptr;
	}
	delete[] m.ptr;
	m.ptr = nullptr;
	
	// update rows and cols
	in >> m.rows;
	in >> m.cols;

	// reallocate
	m.ptr = new int* [m.rows];
	for (int i = 0; i < m.rows; i++)
	{
		m.ptr[i] = new int[m.cols];
	}

	// get values
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			in >> m.ptr[i][j];
		}
	}

	return in;
}



ostream& operator << (ostream& out, const Matrix& m)
{
	// output values
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			out << setw(5) << m.ptr[i][j];
		}
		out << endl;
	}

	return out;
}