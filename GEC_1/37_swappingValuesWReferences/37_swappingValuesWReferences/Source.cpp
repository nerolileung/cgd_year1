#include <iostream>
using namespace std;

void swap(int& rNum1, int& rNum2);

int main() {
	int num1 = 5, num2 = 10;
	cout << "MAIN: Before swap." << endl;
	cout << "num 1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl << endl;

	swap(num1, num2);

	cout << "MAIN: After swap." << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl << endl;

	cin.get();
	return 0;
}

void swap(int& rNum1, int& rNum2) {
	int temp;
	cout << "SWAP: Before swap." << endl;
	cout << "rNum1 = " << rNum1 << endl;
	cout << "rNum2 = " << rNum2 << endl << endl;

	temp = rNum1;
	rNum1 = rNum2;
	rNum2 = temp;
	
	cout << "SWAP: After swap." << endl;
	cout << "rNum1 = " << rNum1 << endl;
	cout << "rNum2 = " << rNum2 << endl << endl;
}