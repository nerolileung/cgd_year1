#include <iostream>
using namespace std;
int main() {
	int arr[5];
	int holder;
	for (int i = 0; i < 5; i++) { // initialise array values
		cout << "Please enter integer #" << i + 1 << ':' << endl;
		cin >> arr[i];
	}
	holder = arr[0];
	cout << "In the order that you entered them, the array values are: ";
	for (int i = 0; i < 5; i++) {
		cout << arr[i];
		if (i != 4)	cout << ", ";
		else cout << endl;
	}
	cout << "In backwards order, the array values are: ";
	for (int i = 4; i > -1; i--) {
		cout << arr[i];
		if (i != 0) cout << ", ";
		else cout << endl;
	}
	cout << "The largest value in this array is ";
	for (int i = 1; i < 5; i++) {
		if (arr[i] > holder) holder = arr[i];
		if (i == 4) {
			cout << arr[i] << " at position " << i;
		}
	}
	cin.get();
	cin.get();
	return 0;
}