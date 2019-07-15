#include <iostream>
#include <chrono> 
#include <thread> 
using namespace std;
using namespace this_thread; // sleep_for, sleep_until 
using namespace chrono_literals; // ns, us, ms, s, h, etc.

int smallerNumber(int a, int b); // function prototype

int main() {
	int a;
	int b;
	bool again = false;
	char againInput;

	do {
		cout << "Please input one integer." << endl;
		cin >> a;
		cout << "Please input another integer." << endl;
		cin >> b;
		cout << "The smallest value is " << smallerNumber(a, b) << endl;
		cout << "Repeat? (Y/N)" << endl;
		cin >> againInput;
		if (againInput == 'Y' || againInput == 'y')	again = true;
		else again = false;

	} while (again);

	sleep_for(5s);
	return 0;
}

int smallerNumber(int a, int b) {
	if (a < b)	return a;
	else	return b;
}