#include <iostream>
#include <chrono> 
#include <thread> 

using namespace std;
using namespace this_thread; // sleep_for, sleep_until 
using namespace chrono_literals; // ns, us, ms, s, h, etc. 
using chrono::system_clock;

int main() {
	int userNum1;
	int userNum2;
	int userNumNewest;
	int userNumCount = 2;
	int sum;
	int mean;
	
	cout << "Please enter a number." << endl;
	cin >> userNum1;
	cout << "Please enter another number." << endl;
	cin >> userNum2;

	sum = userNum1 + userNum2;
	mean = sum / userNumCount;
	cout << "The sum of the numbers you entered is " << sum << ". The mean of the numbers you entered is approximately " << mean << endl;

	do {
		cout << "Please enter another number." << endl;
		cin >> userNumNewest;
		userNumCount++;
		sum += userNumNewest;
		mean = sum / userNumCount;
		cout << "The new sum is " << sum << ". The new mean is approximately " << mean << endl;

		if (userNumNewest == 0) {
			cout << "You found the escape condition! Thank you for participating." << endl;
		}

	} while (userNumNewest != 0);

	sleep_for(5s);
	sleep_until(system_clock::now() + 1s);
	cin.get();
	return 0;
}