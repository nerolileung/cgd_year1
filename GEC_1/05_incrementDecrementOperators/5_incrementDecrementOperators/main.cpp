#include <iostream>
using namespace std;

int main() {
	//single line comment
	/* multi
	line
	comment*/

	int num = 1;

	//result of ++x
	cout << "num = " << num << endl;
	cout << "Increment Operator before num = " << ++num << endl;
	cout << "num after = " << num << endl;

	// result of x++
	num = 1;
	cout << "num = " << num << endl;
	cout << "Increment Operator after num = " << num++ << endl;
	cout << "num after = " << num << endl;

	// result of --x
	num = 1;
	cout << "num = " << num << endl;
	cout << "Decrement Operator before num = " << --num << endl;
	cout << "num after = " << num << endl;

	// result of x--
	num = 1;
	cout << "num = " << num << endl;
	cout << "Decrement Operator after num = " << num-- << endl;
	cout << "num after = " << num << endl;

	cin.get();
	return 0;
}