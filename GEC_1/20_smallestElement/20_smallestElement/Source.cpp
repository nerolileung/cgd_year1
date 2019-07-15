#include <iostream>
using namespace std;

int arr[10];
int smallest;
int smallestPos = 0;
bool again = false;
char againInput;

int main() {
	do {
		for (int i = 0; i < 10; i++) {
			cout << "Please enter integer #" << i + 1 << endl;
			cin >> arr[i];
		}
		smallest = arr[0];
		for (int i = 1; i < 10; i++) {
			if (arr[i] < smallest) {
				smallest = arr[i];
				smallestPos = i;
			}
		}
		cout << "The smallest element of the array has the value " << smallest << " and is at position " << smallestPos << endl;
		cout << "Repeat program? (Y/N)" << endl;;
		cin >> againInput;
		if (againInput == 'Y' || againInput == 'y')	again = true;
		else again = false;
	} while (again);
	cin.get();
	cin.get();
	return 0;
}