#include <iostream>

using namespace std;

bool isOdd(int x);
void outputResults(int numOfOdd, int oddTotal, int numOfEven, int evenTotal);
int x;
int numOfOdd;
int oddTotal;
int numOfEven;
int evenTotal;

int main() {
	for (int i = 1; i < 11; i++) {
		cout << "Please input integer #" << i << ":" << endl;
		cin >> x;
		isOdd(x);
	}

	outputResults(numOfOdd, oddTotal, numOfEven, evenTotal);

	cin.get();
	cin.get(); // 2x lets it actually stay on screen without forcing it to sleep
	return 0;
}

bool isOdd(int x) {
	if (x % 2 == 0) {
		numOfEven++;
		evenTotal += x;
		return false;
	}
	else
	{
		numOfOdd++;
		oddTotal += x;
		return true;
	}
}

void outputResults(int numOfOdd, int oddTotal, int numOfEven, int evenTotal) {
	cout << "Total number of odd integers: " << numOfOdd << endl;
	cout << "Sum of all odd integers: " << oddTotal << endl;
	cout << "Total number of even integers: " << numOfEven << endl;
	cout << "Sum of all even integers: " << evenTotal << endl;
}