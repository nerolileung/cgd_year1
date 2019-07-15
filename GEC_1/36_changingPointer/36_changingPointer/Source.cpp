#include <iostream>
using namespace std;

void inputDetails(int* n1, int* n2);
void outputDetails(int* n1, int* n2, int* pNum);

int main() {
	int num1, num2;
	int* pNum = &num1;
	inputDetails(&num1, &num2);
	outputDetails(&num1, &num2, pNum);
	cout << endl << "Setting pNum to address of num2..." << endl;
	pNum = &num2;
	outputDetails(&num1, &num2, pNum);
	pNum = nullptr;
	cin.ignore();
	cin.get();
	return 0;
}

void inputDetails(int* n1, int* n2) {
	cout << "Please enter an integer." << endl;
	cin >> *n1;
	cout << "Please enter another integer." << endl;
	cin >> *n2;
}

void outputDetails(int* n1, int* n2, int* pNum) {
	cout << "num1 value (*n1): " << *n1 << endl;
	cout << "num1 memory address (n1): " << n1 << endl;
	cout << "num2 value (*n2): " << *n2 << endl;
	cout << "num2 memory address (n2): " << n2 << endl;
	cout << "pNum value: " << pNum << endl;
	cout << "pNum dereferenced value (*pNum): " << *pNum << endl;
	cout << "pNum memory address (&pNum): " << &pNum << endl;
}