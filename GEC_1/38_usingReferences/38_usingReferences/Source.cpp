#include <iostream>
using namespace std;

void addToNum(int& rNum);
void subtractFromNum(int& rNum);

int main() {
	int num;
	cout << "Please enter an integer." << endl;
	cin >> num;
	cout << "The current value of num is " << num << endl;
	addToNum(num);
	cout << "The current value of num is " << num << endl;
	cout << "Please enter another integer." << endl;
	cin >> num;
	cout << "The current value of num is " << num << endl;
	subtractFromNum(num);
	cout << "The current value of num is " << num << endl;
	cin.ignore();
	cin.get();
	return 0;
}

void addToNum(int& rNum) {
	rNum += 25;
}

void subtractFromNum(int& rNum) {
	rNum -= 25;
}