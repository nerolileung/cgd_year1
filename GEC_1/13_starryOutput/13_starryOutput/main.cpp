#include <iostream>
#include <string>
#include <chrono> 
#include <thread> 

using namespace std;
using namespace this_thread; // sleep_for, sleep_until 
using namespace chrono_literals; // ns, us, ms, s, h, etc. 
using chrono::system_clock;

int main() {
	int starNum;
	string starLine;
	char again;

	do {
		cout << "Please enter a number between 1 and 10 (inclusive)." << endl;
		cin >> starNum;

		for (int i = 0; i < starNum; i++) {
			starLine = "";
			for (int j = 0; j < i + 1; j++) { //make sure loop does not skip when i and j = 0
				starLine += "* ";
			}
			cout << starLine << endl;
		}

		cout << "Go again?" << endl;
		cin >> again;
	} while (again == 'Y' || again == 'y');

	cout << "Goodbye." << endl;

	sleep_for(5s);
	cin.get();
	return 0;
}