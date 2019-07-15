#include <iostream>
using namespace std;

void swap(int* pNum1, int* pNum2);

int main() {
	int num1 = 5, num2 = 10;
	cout << "MAIN: Before swap." << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl << endl;
	swap(&num1, &num2); //directly pass in memory addresses without setting pointer variables first
	cout << "MAIN: After swap." << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	cin.get();
	return 0;
}

void swap(int* pNum1, int* pNum2) {
	int temp;
	cout << "SWAP: Before swap." << endl;
	cout << "*pNum1 = " << *pNum1 << endl; //* gets value at memory address pointed to
	cout << "*pNum2 = " << *pNum2 << endl << endl;
	temp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = temp;
	cout << "SWAP: After swap." << endl;
	cout << "*pNum1 = " << *pNum1 << endl;
	cout << "*pNum2 = " << *pNum2 << endl << endl;
}