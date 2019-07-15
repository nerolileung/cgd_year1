#include <iostream>
using namespace std;

void add2ToNumber(int num);

int main() {
	int myNum = 0;
	cout << "MAIN [before]: myNum = " << myNum << endl;
	add2ToNumber(myNum);
	cout << "MAIN [after]: myNum = " << myNum << endl;

	cin.get();
	return 0;
}

void add2ToNumber(int num) {
	num += 2;
	cout << "FUNCTION: num = " << num << endl;
}