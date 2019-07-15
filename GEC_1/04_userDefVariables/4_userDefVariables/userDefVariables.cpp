#include <iostream>

using namespace std;

int main() {
	typedef int date;
	enum Month {
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	date varDate = 15;
	Month varMonth = APRIL;

	cout << "Value of date variable is " << varDate << endl;
	cout << "Value of month variable is " << varMonth << endl;

	cin.get();
	return 0;
}