#include <iostream>
using namespace std;
int main(){
	int num = 5;
	int* pNum = &num;
	cout << "myNum = " << num << endl;
	cout << "pPointerToMyNum = " << pNum << endl;
	cout << "*pPointerToMyNum = " << *pNum << endl; // dereference pointer
	cout << "&myNum = " << &num << endl;
	cout << "pPointerToMyNum = " << pNum << endl;
	cout << "&pPointerToMyNum = " << &pNum << endl;
	cin.get();
	return 0;
}